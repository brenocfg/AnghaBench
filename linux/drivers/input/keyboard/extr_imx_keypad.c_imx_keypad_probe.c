#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct matrix_keymap_data {int dummy; } ;
struct TYPE_12__ {TYPE_3__* parent; } ;
struct TYPE_11__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct imx_keypad {int irq; scalar_t__* keycodes; int rows_en_mask; int cols_en_mask; int /*<<< orphan*/  clk; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  check_matrix_timer; scalar_t__ stable_count; struct input_dev* input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ KEY_RESERVED ; 
 int /*<<< orphan*/  MATRIX_ROW_SHIFT ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int MAX_MATRIX_KEY_COLS ; 
 int MAX_MATRIX_KEY_ROWS ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct matrix_keymap_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_3__*,int) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (TYPE_3__*) ; 
 struct imx_keypad* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct imx_keypad*) ; 
 int /*<<< orphan*/  imx_keypad_check_for_events ; 
 int /*<<< orphan*/  imx_keypad_close ; 
 int /*<<< orphan*/  imx_keypad_inhibit (struct imx_keypad*) ; 
 int /*<<< orphan*/  imx_keypad_irq_handler ; 
 int /*<<< orphan*/  imx_keypad_open ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct imx_keypad*) ; 
 int matrix_keypad_build_keymap (struct matrix_keymap_data const*,int /*<<< orphan*/ *,int,int,scalar_t__*,struct input_dev*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx_keypad*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_keypad_probe(struct platform_device *pdev)
{
	const struct matrix_keymap_data *keymap_data =
			dev_get_platdata(&pdev->dev);
	struct imx_keypad *keypad;
	struct input_dev *input_dev;
	int irq, error, i, row, col;

	if (!keymap_data && !pdev->dev.of_node) {
		dev_err(&pdev->dev, "no keymap defined\n");
		return -EINVAL;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!input_dev) {
		dev_err(&pdev->dev, "failed to allocate the input device\n");
		return -ENOMEM;
	}

	keypad = devm_kzalloc(&pdev->dev, sizeof(*keypad), GFP_KERNEL);
	if (!keypad) {
		dev_err(&pdev->dev, "not enough memory for driver data\n");
		return -ENOMEM;
	}

	keypad->input_dev = input_dev;
	keypad->irq = irq;
	keypad->stable_count = 0;

	timer_setup(&keypad->check_matrix_timer,
		    imx_keypad_check_for_events, 0);

	keypad->mmio_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(keypad->mmio_base))
		return PTR_ERR(keypad->mmio_base);

	keypad->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(keypad->clk)) {
		dev_err(&pdev->dev, "failed to get keypad clock\n");
		return PTR_ERR(keypad->clk);
	}

	/* Init the Input device */
	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.parent = &pdev->dev;
	input_dev->open = imx_keypad_open;
	input_dev->close = imx_keypad_close;

	error = matrix_keypad_build_keymap(keymap_data, NULL,
					   MAX_MATRIX_KEY_ROWS,
					   MAX_MATRIX_KEY_COLS,
					   keypad->keycodes, input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to build keymap\n");
		return error;
	}

	/* Search for rows and cols enabled */
	for (row = 0; row < MAX_MATRIX_KEY_ROWS; row++) {
		for (col = 0; col < MAX_MATRIX_KEY_COLS; col++) {
			i = MATRIX_SCAN_CODE(row, col, MATRIX_ROW_SHIFT);
			if (keypad->keycodes[i] != KEY_RESERVED) {
				keypad->rows_en_mask |= 1 << row;
				keypad->cols_en_mask |= 1 << col;
			}
		}
	}
	dev_dbg(&pdev->dev, "enabled rows mask: %x\n", keypad->rows_en_mask);
	dev_dbg(&pdev->dev, "enabled cols mask: %x\n", keypad->cols_en_mask);

	__set_bit(EV_REP, input_dev->evbit);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	input_set_drvdata(input_dev, keypad);

	/* Ensure that the keypad will stay dormant until opened */
	error = clk_prepare_enable(keypad->clk);
	if (error)
		return error;
	imx_keypad_inhibit(keypad);
	clk_disable_unprepare(keypad->clk);

	error = devm_request_irq(&pdev->dev, irq, imx_keypad_irq_handler, 0,
			    pdev->name, keypad);
	if (error) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		return error;
	}

	/* Register the input device */
	error = input_register_device(input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device\n");
		return error;
	}

	platform_set_drvdata(pdev, keypad);
	device_init_wakeup(&pdev->dev, 1);

	return 0;
}