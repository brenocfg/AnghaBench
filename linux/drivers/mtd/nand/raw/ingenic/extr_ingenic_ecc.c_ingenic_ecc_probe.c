#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ingenic_ecc {struct device* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; TYPE_1__* ops; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct ingenic_ecc*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 TYPE_1__* device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ingenic_ecc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ingenic_ecc*) ; 
 int /*<<< orphan*/  stub1 (struct ingenic_ecc*) ; 

int ingenic_ecc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ingenic_ecc *ecc;
	struct resource *res;

	ecc = devm_kzalloc(dev, sizeof(*ecc), GFP_KERNEL);
	if (!ecc)
		return -ENOMEM;

	ecc->ops = device_get_match_data(dev);
	if (!ecc->ops)
		return -EINVAL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ecc->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(ecc->base))
		return PTR_ERR(ecc->base);

	ecc->ops->disable(ecc);

	ecc->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(ecc->clk)) {
		dev_err(dev, "failed to get clock: %ld\n", PTR_ERR(ecc->clk));
		return PTR_ERR(ecc->clk);
	}

	mutex_init(&ecc->lock);

	ecc->dev = dev;
	platform_set_drvdata(pdev, ecc);

	return 0;
}