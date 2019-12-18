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
struct sunxi_sid_cfg {int size; scalar_t__ need_register_readout; int /*<<< orphan*/  value_offset; } ;
struct sunxi_sid {struct nvmem_device* base; int /*<<< orphan*/  value_offset; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct nvmem_device {int dummy; } ;
struct nvmem_config {char* name; int read_only; int size; int word_size; int stride; int /*<<< orphan*/  (* reg_read ) (struct sunxi_sid*,int /*<<< orphan*/ ,char*,int) ;struct sunxi_sid* priv; struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct nvmem_device*) ; 
 int PTR_ERR (struct nvmem_device*) ; 
 int /*<<< orphan*/  add_device_randomness (char*,int) ; 
 struct nvmem_device* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct nvmem_device* devm_nvmem_register (struct device*,struct nvmem_config*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct sunxi_sid_cfg* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nvmem_device*) ; 
 int /*<<< orphan*/  stub1 (struct sunxi_sid*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sun8i_sid_read_by_reg (struct sunxi_sid*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sunxi_sid_read (struct sunxi_sid*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int sunxi_sid_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct nvmem_config *nvmem_cfg;
	struct nvmem_device *nvmem;
	struct sunxi_sid *sid;
	int size;
	char *randomness;
	const struct sunxi_sid_cfg *cfg;

	sid = devm_kzalloc(dev, sizeof(*sid), GFP_KERNEL);
	if (!sid)
		return -ENOMEM;

	cfg = of_device_get_match_data(dev);
	if (!cfg)
		return -EINVAL;
	sid->value_offset = cfg->value_offset;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	sid->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(sid->base))
		return PTR_ERR(sid->base);

	size = cfg->size;

	nvmem_cfg = devm_kzalloc(dev, sizeof(*nvmem_cfg), GFP_KERNEL);
	if (!nvmem_cfg)
		return -ENOMEM;

	nvmem_cfg->dev = dev;
	nvmem_cfg->name = "sunxi-sid";
	nvmem_cfg->read_only = true;
	nvmem_cfg->size = cfg->size;
	nvmem_cfg->word_size = 1;
	nvmem_cfg->stride = 4;
	nvmem_cfg->priv = sid;
	if (cfg->need_register_readout)
		nvmem_cfg->reg_read = sun8i_sid_read_by_reg;
	else
		nvmem_cfg->reg_read = sunxi_sid_read;

	nvmem = devm_nvmem_register(dev, nvmem_cfg);
	if (IS_ERR(nvmem))
		return PTR_ERR(nvmem);

	randomness = kzalloc(size, GFP_KERNEL);
	if (!randomness)
		return -ENOMEM;

	nvmem_cfg->reg_read(sid, 0, randomness, size);
	add_device_randomness(randomness, size);
	kfree(randomness);

	platform_set_drvdata(pdev, nvmem);

	return 0;
}