#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_10__ {TYPE_2__* parent; struct device_node* of_node; } ;
struct TYPE_12__ {int retries; TYPE_1__ dev; struct exynos5_i2c* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct exynos5_i2c {int irq; int /*<<< orphan*/  clk; TYPE_3__ adap; int /*<<< orphan*/  variant; int /*<<< orphan*/  msg_complete; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; TYPE_2__* dev; int /*<<< orphan*/  op_clock; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HSI2C_FS_TX_CLOCK ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct exynos5_i2c* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct exynos5_i2c*) ; 
 int exynos5_hsi2c_clock_setup (struct exynos5_i2c*) ; 
 int /*<<< orphan*/  exynos5_i2c_algorithm ; 
 int /*<<< orphan*/  exynos5_i2c_clr_pend_irq (struct exynos5_i2c*) ; 
 int /*<<< orphan*/  exynos5_i2c_irq ; 
 int /*<<< orphan*/  exynos5_i2c_reset (struct exynos5_i2c*) ; 
 int i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_get_match_data (TYPE_2__*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct exynos5_i2c*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int exynos5_i2c_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct exynos5_i2c *i2c;
	struct resource *mem;
	int ret;

	i2c = devm_kzalloc(&pdev->dev, sizeof(struct exynos5_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	if (of_property_read_u32(np, "clock-frequency", &i2c->op_clock))
		i2c->op_clock = HSI2C_FS_TX_CLOCK;

	strlcpy(i2c->adap.name, "exynos5-i2c", sizeof(i2c->adap.name));
	i2c->adap.owner   = THIS_MODULE;
	i2c->adap.algo    = &exynos5_i2c_algorithm;
	i2c->adap.retries = 3;

	i2c->dev = &pdev->dev;
	i2c->clk = devm_clk_get(&pdev->dev, "hsi2c");
	if (IS_ERR(i2c->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		return -ENOENT;
	}

	ret = clk_prepare_enable(i2c->clk);
	if (ret)
		return ret;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(i2c->regs)) {
		ret = PTR_ERR(i2c->regs);
		goto err_clk;
	}

	i2c->adap.dev.of_node = np;
	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &pdev->dev;

	/* Clear pending interrupts from u-boot or misc causes */
	exynos5_i2c_clr_pend_irq(i2c);

	spin_lock_init(&i2c->lock);
	init_completion(&i2c->msg_complete);

	i2c->irq = ret = platform_get_irq(pdev, 0);
	if (ret <= 0) {
		dev_err(&pdev->dev, "cannot find HS-I2C IRQ\n");
		ret = -EINVAL;
		goto err_clk;
	}

	ret = devm_request_irq(&pdev->dev, i2c->irq, exynos5_i2c_irq,
			       IRQF_NO_SUSPEND, dev_name(&pdev->dev), i2c);
	if (ret != 0) {
		dev_err(&pdev->dev, "cannot request HS-I2C IRQ %d\n", i2c->irq);
		goto err_clk;
	}

	i2c->variant = of_device_get_match_data(&pdev->dev);

	ret = exynos5_hsi2c_clock_setup(i2c);
	if (ret)
		goto err_clk;

	exynos5_i2c_reset(i2c);

	ret = i2c_add_adapter(&i2c->adap);
	if (ret < 0)
		goto err_clk;

	platform_set_drvdata(pdev, i2c);

	clk_disable(i2c->clk);

	return 0;

 err_clk:
	clk_disable_unprepare(i2c->clk);
	return ret;
}