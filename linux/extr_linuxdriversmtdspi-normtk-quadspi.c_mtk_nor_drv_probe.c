#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mtk_nor {TYPE_1__* dev; void* nor_clk; void* spi_clk; void* base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 void* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct mtk_nor* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_nor_disable_clk (struct mtk_nor*) ; 
 int mtk_nor_enable_clk (struct mtk_nor*) ; 
 int mtk_nor_init (struct mtk_nor*,struct device_node*) ; 
 struct device_node* of_get_next_available_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_nor*) ; 

__attribute__((used)) static int mtk_nor_drv_probe(struct platform_device *pdev)
{
	struct device_node *flash_np;
	struct resource *res;
	int ret;
	struct mtk_nor *mtk_nor;

	if (!pdev->dev.of_node) {
		dev_err(&pdev->dev, "No DT found\n");
		return -EINVAL;
	}

	mtk_nor = devm_kzalloc(&pdev->dev, sizeof(*mtk_nor), GFP_KERNEL);
	if (!mtk_nor)
		return -ENOMEM;
	platform_set_drvdata(pdev, mtk_nor);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mtk_nor->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mtk_nor->base))
		return PTR_ERR(mtk_nor->base);

	mtk_nor->spi_clk = devm_clk_get(&pdev->dev, "spi");
	if (IS_ERR(mtk_nor->spi_clk))
		return PTR_ERR(mtk_nor->spi_clk);

	mtk_nor->nor_clk = devm_clk_get(&pdev->dev, "sf");
	if (IS_ERR(mtk_nor->nor_clk))
		return PTR_ERR(mtk_nor->nor_clk);

	mtk_nor->dev = &pdev->dev;

	ret = mtk_nor_enable_clk(mtk_nor);
	if (ret)
		return ret;

	/* only support one attached flash */
	flash_np = of_get_next_available_child(pdev->dev.of_node, NULL);
	if (!flash_np) {
		dev_err(&pdev->dev, "no SPI flash device to configure\n");
		ret = -ENODEV;
		goto nor_free;
	}
	ret = mtk_nor_init(mtk_nor, flash_np);

nor_free:
	if (ret)
		mtk_nor_disable_clk(mtk_nor);

	return ret;
}