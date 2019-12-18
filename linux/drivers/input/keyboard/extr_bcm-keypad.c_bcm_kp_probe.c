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
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct TYPE_10__ {TYPE_3__* parent; } ;
struct input_dev {char* phys; TYPE_2__ id; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  evbit; } ;
struct bcm_kp {scalar_t__ irq; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * base; int /*<<< orphan*/  n_cols; int /*<<< orphan*/  n_rows; struct input_dev* input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 unsigned int DEFAULT_CLK_HZ ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_kp_close ; 
 int /*<<< orphan*/  bcm_kp_isr_thread ; 
 int bcm_kp_matrix_key_parse_dt (struct bcm_kp*) ; 
 int /*<<< orphan*/  bcm_kp_open ; 
 int /*<<< orphan*/  bcm_kp_stop (struct bcm_kp*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 long clk_round_rate (int /*<<< orphan*/ *,unsigned int) ; 
 int clk_set_rate (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_3__*,char*) ; 
 struct input_dev* devm_input_allocate_device (TYPE_3__*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct bcm_kp* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcm_kp*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct bcm_kp*) ; 
 int matrix_keypad_build_keymap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct input_dev*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_kp_probe(struct platform_device *pdev)
{
	struct bcm_kp *kp;
	struct input_dev *input_dev;
	struct resource *res;
	int error;

	kp = devm_kzalloc(&pdev->dev, sizeof(*kp), GFP_KERNEL);
	if (!kp)
		return -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!input_dev) {
		dev_err(&pdev->dev, "failed to allocate the input device\n");
		return -ENOMEM;
	}

	__set_bit(EV_KEY, input_dev->evbit);

	/* Enable auto repeat feature of Linux input subsystem */
	if (of_property_read_bool(pdev->dev.of_node, "autorepeat"))
		__set_bit(EV_REP, input_dev->evbit);

	input_dev->name = pdev->name;
	input_dev->phys = "keypad/input0";
	input_dev->dev.parent = &pdev->dev;
	input_dev->open = bcm_kp_open;
	input_dev->close = bcm_kp_close;

	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendor = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;

	input_set_drvdata(input_dev, kp);

	kp->input_dev = input_dev;

	error = bcm_kp_matrix_key_parse_dt(kp);
	if (error)
		return error;

	error = matrix_keypad_build_keymap(NULL, NULL,
					   kp->n_rows, kp->n_cols,
					   NULL, input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to build keymap\n");
		return error;
	}

	/* Get the KEYPAD base address */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "Missing keypad base address resource\n");
		return -ENODEV;
	}

	kp->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(kp->base))
		return PTR_ERR(kp->base);

	/* Enable clock */
	kp->clk = devm_clk_get(&pdev->dev, "peri_clk");
	if (IS_ERR(kp->clk)) {
		error = PTR_ERR(kp->clk);
		if (error != -ENOENT) {
			if (error != -EPROBE_DEFER)
				dev_err(&pdev->dev, "Failed to get clock\n");
			return error;
		}
		dev_dbg(&pdev->dev,
			"No clock specified. Assuming it's enabled\n");
		kp->clk = NULL;
	} else {
		unsigned int desired_rate;
		long actual_rate;

		error = of_property_read_u32(pdev->dev.of_node,
					     "clock-frequency", &desired_rate);
		if (error < 0)
			desired_rate = DEFAULT_CLK_HZ;

		actual_rate = clk_round_rate(kp->clk, desired_rate);
		if (actual_rate <= 0)
			return -EINVAL;

		error = clk_set_rate(kp->clk, actual_rate);
		if (error)
			return error;

		error = clk_prepare_enable(kp->clk);
		if (error)
			return error;
	}

	/* Put the kp into a known sane state */
	bcm_kp_stop(kp);

	kp->irq = platform_get_irq(pdev, 0);
	if (kp->irq < 0)
		return -EINVAL;

	error = devm_request_threaded_irq(&pdev->dev, kp->irq,
					  NULL, bcm_kp_isr_thread,
					  IRQF_ONESHOT, pdev->name, kp);
	if (error) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		return error;
	}

	error = input_register_device(input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device\n");
		return error;
	}

	return 0;
}