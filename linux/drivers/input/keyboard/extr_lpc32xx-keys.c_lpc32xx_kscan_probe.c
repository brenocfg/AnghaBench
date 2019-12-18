#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct lpc32xx_kscan_drv {int matrix_sz; int row_shift; int deb_clks; int scan_delay; struct input_dev* input; int /*<<< orphan*/  clk; int /*<<< orphan*/  kscan_base; void* keymap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int vendor; int product; int version; } ;
struct input_dev {char* phys; TYPE_2__ dev; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int LPC32XX_KSCAN_FTST_USE32K_CLK ; 
 int /*<<< orphan*/  LPC32XX_KS_DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_KS_FAST_TST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_KS_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_KS_MATRIX_DIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_KS_SCAN_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpc32xx_kscan_drv*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct lpc32xx_kscan_drv*) ; 
 int /*<<< orphan*/  lpc32xx_kscan_close ; 
 int /*<<< orphan*/  lpc32xx_kscan_irq ; 
 int /*<<< orphan*/  lpc32xx_kscan_open ; 
 int lpc32xx_parse_dt (int /*<<< orphan*/ *,struct lpc32xx_kscan_drv*) ; 
 int matrix_keypad_build_keymap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,void*,struct input_dev*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc32xx_kscan_drv*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc32xx_kscan_probe(struct platform_device *pdev)
{
	struct lpc32xx_kscan_drv *kscandat;
	struct input_dev *input;
	struct resource *res;
	size_t keymap_size;
	int error;
	int irq;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "failed to get platform I/O memory\n");
		return -EINVAL;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -EINVAL;

	kscandat = devm_kzalloc(&pdev->dev, sizeof(*kscandat),
				GFP_KERNEL);
	if (!kscandat)
		return -ENOMEM;

	error = lpc32xx_parse_dt(&pdev->dev, kscandat);
	if (error) {
		dev_err(&pdev->dev, "failed to parse device tree\n");
		return error;
	}

	keymap_size = sizeof(kscandat->keymap[0]) *
				(kscandat->matrix_sz << kscandat->row_shift);
	kscandat->keymap = devm_kzalloc(&pdev->dev, keymap_size, GFP_KERNEL);
	if (!kscandat->keymap)
		return -ENOMEM;

	kscandat->input = input = devm_input_allocate_device(&pdev->dev);
	if (!input) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	/* Setup key input */
	input->name		= pdev->name;
	input->phys		= "lpc32xx/input0";
	input->id.vendor	= 0x0001;
	input->id.product	= 0x0001;
	input->id.version	= 0x0100;
	input->open		= lpc32xx_kscan_open;
	input->close		= lpc32xx_kscan_close;
	input->dev.parent	= &pdev->dev;

	input_set_capability(input, EV_MSC, MSC_SCAN);

	error = matrix_keypad_build_keymap(NULL, NULL,
					   kscandat->matrix_sz,
					   kscandat->matrix_sz,
					   kscandat->keymap, kscandat->input);
	if (error) {
		dev_err(&pdev->dev, "failed to build keymap\n");
		return error;
	}

	input_set_drvdata(kscandat->input, kscandat);

	kscandat->kscan_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(kscandat->kscan_base))
		return PTR_ERR(kscandat->kscan_base);

	/* Get the key scanner clock */
	kscandat->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(kscandat->clk)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		return PTR_ERR(kscandat->clk);
	}

	/* Configure the key scanner */
	error = clk_prepare_enable(kscandat->clk);
	if (error)
		return error;

	writel(kscandat->deb_clks, LPC32XX_KS_DEB(kscandat->kscan_base));
	writel(kscandat->scan_delay, LPC32XX_KS_SCAN_CTL(kscandat->kscan_base));
	writel(LPC32XX_KSCAN_FTST_USE32K_CLK,
	       LPC32XX_KS_FAST_TST(kscandat->kscan_base));
	writel(kscandat->matrix_sz,
	       LPC32XX_KS_MATRIX_DIM(kscandat->kscan_base));
	writel(1, LPC32XX_KS_IRQ(kscandat->kscan_base));
	clk_disable_unprepare(kscandat->clk);

	error = devm_request_irq(&pdev->dev, irq, lpc32xx_kscan_irq, 0,
				 pdev->name, kscandat);
	if (error) {
		dev_err(&pdev->dev, "failed to request irq\n");
		return error;
	}

	error = input_register_device(kscandat->input);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device\n");
		return error;
	}

	platform_set_drvdata(pdev, kscandat);

	return 0;
}