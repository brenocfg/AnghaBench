#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct stmpe_keypad {struct input_dev* input; int /*<<< orphan*/  no_autorepeat; int /*<<< orphan*/  keymap; int /*<<< orphan*/  scan_count; int /*<<< orphan*/  debounce_ms; int /*<<< orphan*/ * variant; struct stmpe* stmpe; } ;
struct stmpe {size_t partnum; } ;
struct TYPE_10__ {struct device_node* of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_9__ {TYPE_3__* parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  evbit; TYPE_2__ dev; TYPE_1__ id; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_I2C ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct stmpe* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (TYPE_3__*) ; 
 struct stmpe_keypad* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct stmpe_keypad*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int matrix_keypad_build_keymap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct input_dev*) ; 
 int matrix_keypad_parse_properties (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stmpe_keypad*) ; 
 int stmpe_keypad_chip_init (struct stmpe_keypad*) ; 
 int /*<<< orphan*/  stmpe_keypad_fill_used_pins (struct stmpe_keypad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmpe_keypad_irq ; 
 int /*<<< orphan*/ * stmpe_keypad_variants ; 

__attribute__((used)) static int stmpe_keypad_probe(struct platform_device *pdev)
{
	struct stmpe *stmpe = dev_get_drvdata(pdev->dev.parent);
	struct device_node *np = pdev->dev.of_node;
	struct stmpe_keypad *keypad;
	struct input_dev *input;
	u32 rows;
	u32 cols;
	int error;
	int irq;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	keypad = devm_kzalloc(&pdev->dev, sizeof(struct stmpe_keypad),
			      GFP_KERNEL);
	if (!keypad)
		return -ENOMEM;

	keypad->stmpe = stmpe;
	keypad->variant = &stmpe_keypad_variants[stmpe->partnum];

	of_property_read_u32(np, "debounce-interval", &keypad->debounce_ms);
	of_property_read_u32(np, "st,scan-count", &keypad->scan_count);
	keypad->no_autorepeat = of_property_read_bool(np, "st,no-autorepeat");

	input = devm_input_allocate_device(&pdev->dev);
	if (!input)
		return -ENOMEM;

	input->name = "STMPE keypad";
	input->id.bustype = BUS_I2C;
	input->dev.parent = &pdev->dev;

	error = matrix_keypad_parse_properties(&pdev->dev, &rows, &cols);
	if (error)
		return error;

	error = matrix_keypad_build_keymap(NULL, NULL, rows, cols,
					   keypad->keymap, input);
	if (error)
		return error;

	input_set_capability(input, EV_MSC, MSC_SCAN);
	if (!keypad->no_autorepeat)
		__set_bit(EV_REP, input->evbit);

	stmpe_keypad_fill_used_pins(keypad, rows, cols);

	keypad->input = input;

	error = stmpe_keypad_chip_init(keypad);
	if (error < 0)
		return error;

	error = devm_request_threaded_irq(&pdev->dev, irq,
					  NULL, stmpe_keypad_irq,
					  IRQF_ONESHOT, "stmpe-keypad", keypad);
	if (error) {
		dev_err(&pdev->dev, "unable to get irq: %d\n", error);
		return error;
	}

	error = input_register_device(input);
	if (error) {
		dev_err(&pdev->dev,
			"unable to register input device: %d\n", error);
		return error;
	}

	platform_set_drvdata(pdev, keypad);

	return 0;
}