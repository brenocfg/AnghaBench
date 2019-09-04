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
typedef  int u8 ;
struct twl4030_keypad_data {scalar_t__ rows; scalar_t__ cols; int rep; struct matrix_keymap_data* keymap_data; } ;
struct twl4030_keypad {scalar_t__ n_rows; scalar_t__ n_cols; int autorepeat; int /*<<< orphan*/  irq; int /*<<< orphan*/ * dbg_dev; int /*<<< orphan*/  keymap; struct input_dev* input; } ;
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct matrix_keymap_data {int dummy; } ;
struct TYPE_2__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; char* phys; int /*<<< orphan*/  evbit; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KEYP_IMR1 ; 
 int KEYP_IMR1_KP ; 
 int KEYP_IMR1_TO ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 scalar_t__ TWL4030_MAX_COLS ; 
 scalar_t__ TWL4030_MAX_ROWS ; 
 int TWL4030_ROW_SHIFT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct twl4030_keypad_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct twl4030_keypad* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct twl4030_keypad*) ; 
 int /*<<< orphan*/  do_kp_irq ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int matrix_keypad_build_keymap (struct matrix_keymap_data const*,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,struct input_dev*) ; 
 int matrix_keypad_parse_properties (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int twl4030_kp_program (struct twl4030_keypad*) ; 
 scalar_t__ twl4030_kpwrite_u8 (struct twl4030_keypad*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_kp_probe(struct platform_device *pdev)
{
	struct twl4030_keypad_data *pdata = dev_get_platdata(&pdev->dev);
	const struct matrix_keymap_data *keymap_data = NULL;
	struct twl4030_keypad *kp;
	struct input_dev *input;
	u8 reg;
	int error;

	kp = devm_kzalloc(&pdev->dev, sizeof(*kp), GFP_KERNEL);
	if (!kp)
		return -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	if (!input)
		return -ENOMEM;

	/* get the debug device */
	kp->dbg_dev		= &pdev->dev;
	kp->input		= input;

	/* setup input device */
	input->name		= "TWL4030 Keypad";
	input->phys		= "twl4030_keypad/input0";

	input->id.bustype	= BUS_HOST;
	input->id.vendor	= 0x0001;
	input->id.product	= 0x0001;
	input->id.version	= 0x0003;

	if (pdata) {
		if (!pdata->rows || !pdata->cols || !pdata->keymap_data) {
			dev_err(&pdev->dev, "Missing platform_data\n");
			return -EINVAL;
		}

		kp->n_rows = pdata->rows;
		kp->n_cols = pdata->cols;
		kp->autorepeat = pdata->rep;
		keymap_data = pdata->keymap_data;
	} else {
		error = matrix_keypad_parse_properties(&pdev->dev, &kp->n_rows,
						       &kp->n_cols);
		if (error)
			return error;

		kp->autorepeat = true;
	}

	if (kp->n_rows > TWL4030_MAX_ROWS || kp->n_cols > TWL4030_MAX_COLS) {
		dev_err(&pdev->dev,
			"Invalid rows/cols amount specified in platform/devicetree data\n");
		return -EINVAL;
	}

	kp->irq = platform_get_irq(pdev, 0);
	if (!kp->irq) {
		dev_err(&pdev->dev, "no keyboard irq assigned\n");
		return -EINVAL;
	}

	error = matrix_keypad_build_keymap(keymap_data, NULL,
					   TWL4030_MAX_ROWS,
					   1 << TWL4030_ROW_SHIFT,
					   kp->keymap, input);
	if (error) {
		dev_err(kp->dbg_dev, "Failed to build keymap\n");
		return error;
	}

	input_set_capability(input, EV_MSC, MSC_SCAN);
	/* Enable auto repeat feature of Linux input subsystem */
	if (kp->autorepeat)
		__set_bit(EV_REP, input->evbit);

	error = input_register_device(input);
	if (error) {
		dev_err(kp->dbg_dev,
			"Unable to register twl4030 keypad device\n");
		return error;
	}

	error = twl4030_kp_program(kp);
	if (error)
		return error;

	/*
	 * This ISR will always execute in kernel thread context because of
	 * the need to access the TWL4030 over the I2C bus.
	 *
	 * NOTE:  we assume this host is wired to TWL4040 INT1, not INT2 ...
	 */
	error = devm_request_threaded_irq(&pdev->dev, kp->irq, NULL, do_kp_irq,
					  0, pdev->name, kp);
	if (error) {
		dev_info(kp->dbg_dev, "request_irq failed for irq no=%d: %d\n",
			kp->irq, error);
		return error;
	}

	/* Enable KP and TO interrupts now. */
	reg = (u8) ~(KEYP_IMR1_KP | KEYP_IMR1_TO);
	if (twl4030_kpwrite_u8(kp, reg, KEYP_IMR1)) {
		/* mask all events - we don't care about the result */
		(void) twl4030_kpwrite_u8(kp, 0xff, KEYP_IMR1);
		return -EIO;
	}

	return 0;
}