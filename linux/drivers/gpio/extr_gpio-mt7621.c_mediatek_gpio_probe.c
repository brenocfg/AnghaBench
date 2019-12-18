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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct mtk {struct device* dev; int /*<<< orphan*/  gpio_irq; int /*<<< orphan*/  base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MTK_BANK_CNT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct mtk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int mediatek_gpio_bank_probe (struct device*,struct device_node*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk*) ; 

__attribute__((used)) static int
mediatek_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct mtk *mtk;
	int i;
	int ret;

	mtk = devm_kzalloc(dev, sizeof(*mtk), GFP_KERNEL);
	if (!mtk)
		return -ENOMEM;

	mtk->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(mtk->base))
		return PTR_ERR(mtk->base);

	mtk->gpio_irq = irq_of_parse_and_map(np, 0);
	mtk->dev = dev;
	platform_set_drvdata(pdev, mtk);

	for (i = 0; i < MTK_BANK_CNT; i++) {
		ret = mediatek_gpio_bank_probe(dev, np, i);
		if (ret)
			return ret;
	}

	return 0;
}