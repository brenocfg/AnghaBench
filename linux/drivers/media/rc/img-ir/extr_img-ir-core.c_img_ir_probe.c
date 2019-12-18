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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct img_ir_priv {int irq; void* sys_clk; void* clk; void* reg_base; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct img_ir_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_ident (struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_isr ; 
 int img_ir_probe_hw (struct img_ir_priv*) ; 
 int img_ir_probe_raw (struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_remove_hw (struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_remove_raw (struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_setup (struct img_ir_priv*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct img_ir_priv*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct img_ir_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int img_ir_probe(struct platform_device *pdev)
{
	struct img_ir_priv *priv;
	struct resource *res_regs;
	int irq, error, error2;

	/* Get resources from platform device */
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	/* Private driver data */
	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);
	priv->dev = &pdev->dev;
	spin_lock_init(&priv->lock);

	/* Ioremap the registers */
	res_regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->reg_base = devm_ioremap_resource(&pdev->dev, res_regs);
	if (IS_ERR(priv->reg_base))
		return PTR_ERR(priv->reg_base);

	/* Get core clock */
	priv->clk = devm_clk_get(&pdev->dev, "core");
	if (IS_ERR(priv->clk))
		dev_warn(&pdev->dev, "cannot get core clock resource\n");

	/* Get sys clock */
	priv->sys_clk = devm_clk_get(&pdev->dev, "sys");
	if (IS_ERR(priv->sys_clk))
		dev_warn(&pdev->dev, "cannot get sys clock resource\n");
	/*
	 * Enabling the system clock before the register interface is
	 * accessed. ISR shouldn't get called with Sys Clock disabled,
	 * hence exiting probe with an error.
	 */
	if (!IS_ERR(priv->sys_clk)) {
		error = clk_prepare_enable(priv->sys_clk);
		if (error) {
			dev_err(&pdev->dev, "cannot enable sys clock\n");
			return error;
		}
	}

	/* Set up raw & hw decoder */
	error = img_ir_probe_raw(priv);
	error2 = img_ir_probe_hw(priv);
	if (error && error2) {
		if (error == -ENODEV)
			error = error2;
		goto err_probe;
	}

	/* Get the IRQ */
	priv->irq = irq;
	error = request_irq(priv->irq, img_ir_isr, 0, "img-ir", priv);
	if (error) {
		dev_err(&pdev->dev, "cannot register IRQ %u\n",
			priv->irq);
		error = -EIO;
		goto err_irq;
	}

	img_ir_ident(priv);
	img_ir_setup(priv);

	return 0;

err_irq:
	img_ir_remove_hw(priv);
	img_ir_remove_raw(priv);
err_probe:
	if (!IS_ERR(priv->sys_clk))
		clk_disable_unprepare(priv->sys_clk);
	return error;
}