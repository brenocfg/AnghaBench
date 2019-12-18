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
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct meson_nfc {scalar_t__ reg_base; scalar_t__ reg_clk; struct device* dev; int /*<<< orphan*/  completion; int /*<<< orphan*/  chips; int /*<<< orphan*/  controller; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 scalar_t__ NFC_REG_CFG ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct meson_nfc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct meson_nfc*) ; 
 int dma_set_mask (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int meson_nfc_clk_init (struct meson_nfc*) ; 
 int /*<<< orphan*/  meson_nfc_disable_clk (struct meson_nfc*) ; 
 int /*<<< orphan*/  meson_nfc_irq ; 
 int meson_nfc_nand_chips_init (struct device*,struct meson_nfc*) ; 
 int /*<<< orphan*/  nand_controller_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_nfc*) ; 
 scalar_t__ syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_nfc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct meson_nfc *nfc;
	struct resource *res;
	int ret, irq;

	nfc = devm_kzalloc(dev, sizeof(*nfc), GFP_KERNEL);
	if (!nfc)
		return -ENOMEM;

	nfc->data = of_device_get_match_data(&pdev->dev);
	if (!nfc->data)
		return -ENODEV;

	nand_controller_init(&nfc->controller);
	INIT_LIST_HEAD(&nfc->chips);
	init_completion(&nfc->completion);

	nfc->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	nfc->reg_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(nfc->reg_base))
		return PTR_ERR(nfc->reg_base);

	nfc->reg_clk =
		syscon_regmap_lookup_by_phandle(dev->of_node,
						"amlogic,mmc-syscon");
	if (IS_ERR(nfc->reg_clk)) {
		dev_err(dev, "Failed to lookup clock base\n");
		return PTR_ERR(nfc->reg_clk);
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "no NFC IRQ resource\n");
		return -EINVAL;
	}

	ret = meson_nfc_clk_init(nfc);
	if (ret) {
		dev_err(dev, "failed to initialize NAND clock\n");
		return ret;
	}

	writel(0, nfc->reg_base + NFC_REG_CFG);
	ret = devm_request_irq(dev, irq, meson_nfc_irq, 0, dev_name(dev), nfc);
	if (ret) {
		dev_err(dev, "failed to request NFC IRQ\n");
		ret = -EINVAL;
		goto err_clk;
	}

	ret = dma_set_mask(dev, DMA_BIT_MASK(32));
	if (ret) {
		dev_err(dev, "failed to set DMA mask\n");
		goto err_clk;
	}

	platform_set_drvdata(pdev, nfc);

	ret = meson_nfc_nand_chips_init(dev, nfc);
	if (ret) {
		dev_err(dev, "failed to init NAND chips\n");
		goto err_clk;
	}

	return 0;
err_clk:
	meson_nfc_disable_clk(nfc);
	return ret;
}