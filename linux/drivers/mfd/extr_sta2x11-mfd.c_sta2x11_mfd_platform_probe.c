#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sta2x11_mfd {int /*<<< orphan*/ * regmap; int /*<<< orphan*/ * regs; int /*<<< orphan*/  lock; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct regmap_config {int /*<<< orphan*/  cache_type; int /*<<< orphan*/ * lock_arg; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pci_dev {int dummy; } ;
typedef  enum sta2x11_mfd_plat_dev { ____Placeholder_sta2x11_mfd_plat_dev } sta2x11_mfd_plat_dev ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGCACHE_NONE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct pci_dev** dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_mmio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct regmap_config*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct sta2x11_mfd* sta2x11_mfd_find (struct pci_dev*) ; 
 char** sta2x11_mfd_names ; 
 struct regmap_config** sta2x11_mfd_regmap_configs ; 

__attribute__((used)) static int sta2x11_mfd_platform_probe(struct platform_device *dev,
				      enum sta2x11_mfd_plat_dev index)
{
	struct pci_dev **pdev;
	struct sta2x11_mfd *mfd;
	struct resource *res;
	const char *name = sta2x11_mfd_names[index];
	struct regmap_config *regmap_config = sta2x11_mfd_regmap_configs[index];

	pdev = dev_get_platdata(&dev->dev);
	mfd = sta2x11_mfd_find(*pdev);
	if (!mfd)
		return -ENODEV;
	if (!regmap_config)
		return -ENODEV;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENOMEM;

	if (!request_mem_region(res->start, resource_size(res), name))
		return -EBUSY;

	mfd->regs[index] = ioremap(res->start, resource_size(res));
	if (!mfd->regs[index]) {
		release_mem_region(res->start, resource_size(res));
		return -ENOMEM;
	}
	regmap_config->lock_arg = &mfd->lock;
	/*
	   No caching, registers could be reached both via regmap and via
	   void __iomem *
	*/
	regmap_config->cache_type = REGCACHE_NONE;
	mfd->regmap[index] = devm_regmap_init_mmio(&dev->dev, mfd->regs[index],
						   regmap_config);
	WARN_ON(IS_ERR(mfd->regmap[index]));

	return 0;
}