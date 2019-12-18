#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_12__ {TYPE_3__* parent; int /*<<< orphan*/  of_node; } ;
struct TYPE_15__ {int timeout; int retries; int /*<<< orphan*/  name; int /*<<< orphan*/  quirks; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; TYPE_1__ dev; } ;
struct mtk_i2c {TYPE_4__ adap; TYPE_2__* dev_comp; struct clk* clk_pmic; scalar_t__ have_pmic; struct clk* clk_main; struct clk* clk_arb; struct clk* clk_dma; int /*<<< orphan*/  clk_src_div; TYPE_3__* dev; int /*<<< orphan*/  msg_complete; struct clk* pdmabase; struct clk* base; } ;
struct clk {int dummy; } ;
struct TYPE_13__ {scalar_t__ support_33bits; int /*<<< orphan*/  pmic_i2c; scalar_t__ timing_adjust; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  I2C_DEFAULT_CLK_DIV ; 
 int /*<<< orphan*/  I2C_DRV_NAME ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_NONE ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 void* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct mtk_i2c* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtk_i2c*) ; 
 int dma_set_mask (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct mtk_i2c*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_i2c_algorithm ; 
 int /*<<< orphan*/  mtk_i2c_clock_disable (struct mtk_i2c*) ; 
 int mtk_i2c_clock_enable (struct mtk_i2c*) ; 
 int /*<<< orphan*/  mtk_i2c_init_hw (struct mtk_i2c*) ; 
 int /*<<< orphan*/  mtk_i2c_irq ; 
 int mtk_i2c_parse_dt (int /*<<< orphan*/ ,struct mtk_i2c*) ; 
 int mtk_i2c_set_speed (struct mtk_i2c*,int /*<<< orphan*/ ) ; 
 TYPE_2__* of_device_get_match_data (TYPE_3__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_i2c*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtk_i2c_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct mtk_i2c *i2c;
	struct clk *clk;
	struct resource *res;
	int irq;

	i2c = devm_kzalloc(&pdev->dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c->base))
		return PTR_ERR(i2c->base);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	i2c->pdmabase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c->pdmabase))
		return PTR_ERR(i2c->pdmabase);

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq;

	init_completion(&i2c->msg_complete);

	i2c->dev_comp = of_device_get_match_data(&pdev->dev);
	i2c->adap.dev.of_node = pdev->dev.of_node;
	i2c->dev = &pdev->dev;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &mtk_i2c_algorithm;
	i2c->adap.quirks = i2c->dev_comp->quirks;
	i2c->adap.timeout = 2 * HZ;
	i2c->adap.retries = 1;

	ret = mtk_i2c_parse_dt(pdev->dev.of_node, i2c);
	if (ret)
		return -EINVAL;

	if (i2c->dev_comp->timing_adjust)
		i2c->clk_src_div *= I2C_DEFAULT_CLK_DIV;

	if (i2c->have_pmic && !i2c->dev_comp->pmic_i2c)
		return -EINVAL;

	i2c->clk_main = devm_clk_get(&pdev->dev, "main");
	if (IS_ERR(i2c->clk_main)) {
		dev_err(&pdev->dev, "cannot get main clock\n");
		return PTR_ERR(i2c->clk_main);
	}

	i2c->clk_dma = devm_clk_get(&pdev->dev, "dma");
	if (IS_ERR(i2c->clk_dma)) {
		dev_err(&pdev->dev, "cannot get dma clock\n");
		return PTR_ERR(i2c->clk_dma);
	}

	i2c->clk_arb = devm_clk_get(&pdev->dev, "arb");
	if (IS_ERR(i2c->clk_arb))
		i2c->clk_arb = NULL;

	clk = i2c->clk_main;
	if (i2c->have_pmic) {
		i2c->clk_pmic = devm_clk_get(&pdev->dev, "pmic");
		if (IS_ERR(i2c->clk_pmic)) {
			dev_err(&pdev->dev, "cannot get pmic clock\n");
			return PTR_ERR(i2c->clk_pmic);
		}
		clk = i2c->clk_pmic;
	}

	strlcpy(i2c->adap.name, I2C_DRV_NAME, sizeof(i2c->adap.name));

	ret = mtk_i2c_set_speed(i2c, clk_get_rate(clk));
	if (ret) {
		dev_err(&pdev->dev, "Failed to set the speed.\n");
		return -EINVAL;
	}

	if (i2c->dev_comp->support_33bits) {
		ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(33));
		if (ret) {
			dev_err(&pdev->dev, "dma_set_mask return error.\n");
			return ret;
		}
	}

	ret = mtk_i2c_clock_enable(i2c);
	if (ret) {
		dev_err(&pdev->dev, "clock enable failed!\n");
		return ret;
	}
	mtk_i2c_init_hw(i2c);
	mtk_i2c_clock_disable(i2c);

	ret = devm_request_irq(&pdev->dev, irq, mtk_i2c_irq,
			       IRQF_TRIGGER_NONE, I2C_DRV_NAME, i2c);
	if (ret < 0) {
		dev_err(&pdev->dev,
			"Request I2C IRQ %d fail\n", irq);
		return ret;
	}

	i2c_set_adapdata(&i2c->adap, i2c);
	ret = i2c_add_adapter(&i2c->adap);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, i2c);

	return 0;
}