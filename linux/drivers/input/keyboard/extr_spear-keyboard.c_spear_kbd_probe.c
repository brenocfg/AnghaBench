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
struct spear_kbd {int irq; int /*<<< orphan*/  clk; scalar_t__ rep; int /*<<< orphan*/  keycodes; int /*<<< orphan*/  io_base; int /*<<< orphan*/  suspended_rate; int /*<<< orphan*/  mode; struct input_dev* input; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct matrix_keymap_data {int dummy; } ;
struct kbd_platform_data {int /*<<< orphan*/  suspended_rate; scalar_t__ rep; int /*<<< orphan*/  mode; struct matrix_keymap_data* keymap; } ;
struct TYPE_2__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; char* phys; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  NUM_COLS ; 
 int /*<<< orphan*/  NUM_ROWS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct kbd_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct spear_kbd* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct spear_kbd*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct spear_kbd*) ; 
 int matrix_keypad_build_keymap (struct matrix_keymap_data const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct input_dev*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spear_kbd*) ; 
 int /*<<< orphan*/  spear_kbd_close ; 
 int /*<<< orphan*/  spear_kbd_interrupt ; 
 int /*<<< orphan*/  spear_kbd_open ; 
 int spear_kbd_parse_dt (struct platform_device*,struct spear_kbd*) ; 

__attribute__((used)) static int spear_kbd_probe(struct platform_device *pdev)
{
	struct kbd_platform_data *pdata = dev_get_platdata(&pdev->dev);
	const struct matrix_keymap_data *keymap = pdata ? pdata->keymap : NULL;
	struct spear_kbd *kbd;
	struct input_dev *input_dev;
	struct resource *res;
	int irq;
	int error;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	kbd = devm_kzalloc(&pdev->dev, sizeof(*kbd), GFP_KERNEL);
	if (!kbd) {
		dev_err(&pdev->dev, "not enough memory for driver data\n");
		return -ENOMEM;
	}

	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!input_dev) {
		dev_err(&pdev->dev, "unable to allocate input device\n");
		return -ENOMEM;
	}

	kbd->input = input_dev;
	kbd->irq = irq;

	if (!pdata) {
		error = spear_kbd_parse_dt(pdev, kbd);
		if (error)
			return error;
	} else {
		kbd->mode = pdata->mode;
		kbd->rep = pdata->rep;
		kbd->suspended_rate = pdata->suspended_rate;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	kbd->io_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(kbd->io_base))
		return PTR_ERR(kbd->io_base);

	kbd->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(kbd->clk))
		return PTR_ERR(kbd->clk);

	input_dev->name = "Spear Keyboard";
	input_dev->phys = "keyboard/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendor = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->open = spear_kbd_open;
	input_dev->close = spear_kbd_close;

	error = matrix_keypad_build_keymap(keymap, NULL, NUM_ROWS, NUM_COLS,
					   kbd->keycodes, input_dev);
	if (error) {
		dev_err(&pdev->dev, "Failed to build keymap\n");
		return error;
	}

	if (kbd->rep)
		__set_bit(EV_REP, input_dev->evbit);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);

	input_set_drvdata(input_dev, kbd);

	error = devm_request_irq(&pdev->dev, irq, spear_kbd_interrupt, 0,
			"keyboard", kbd);
	if (error) {
		dev_err(&pdev->dev, "request_irq failed\n");
		return error;
	}

	error = clk_prepare(kbd->clk);
	if (error)
		return error;

	error = input_register_device(input_dev);
	if (error) {
		dev_err(&pdev->dev, "Unable to register keyboard device\n");
		clk_unprepare(kbd->clk);
		return error;
	}

	device_init_wakeup(&pdev->dev, 1);
	platform_set_drvdata(pdev, kbd);

	return 0;
}