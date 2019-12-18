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
typedef  int u32 ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct gemini_ethernet {int /*<<< orphan*/  freeq_lock; int /*<<< orphan*/  irq_lock; scalar_t__ base; struct device* dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GLOBAL_TOE_VERSION_REG ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct gemini_ethernet* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gemini_ethernet*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gemini_ethernet_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct gemini_ethernet *geth;
	unsigned int retry = 5;
	struct resource *res;
	u32 val;

	/* Global registers */
	geth = devm_kzalloc(dev, sizeof(*geth), GFP_KERNEL);
	if (!geth)
		return -ENOMEM;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;
	geth->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(geth->base))
		return PTR_ERR(geth->base);
	geth->dev = dev;

	/* Wait for ports to stabilize */
	do {
		udelay(2);
		val = readl(geth->base + GLOBAL_TOE_VERSION_REG);
		barrier();
	} while (!val && --retry);
	if (!retry) {
		dev_err(dev, "failed to reset ethernet\n");
		return -EIO;
	}
	dev_info(dev, "Ethernet device ID: 0x%03x, revision 0x%01x\n",
		 (val >> 4) & 0xFFFU, val & 0xFU);

	spin_lock_init(&geth->irq_lock);
	spin_lock_init(&geth->freeq_lock);

	/* The children will use this */
	platform_set_drvdata(pdev, geth);

	/* Spawn child devices for the two ports */
	return devm_of_platform_populate(dev);
}