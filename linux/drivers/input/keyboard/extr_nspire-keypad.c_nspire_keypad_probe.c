#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct nspire_keypad {scalar_t__ active_low; int /*<<< orphan*/  scan_interval; int /*<<< orphan*/  row_delay; struct input_dev* input; int /*<<< orphan*/  reg_base; int /*<<< orphan*/  clk; int /*<<< orphan*/  row_shift; } ;
struct TYPE_9__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYPAD_BITMASK_COLS ; 
 int /*<<< orphan*/  KEYPAD_BITMASK_ROWS ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct nspire_keypad* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct nspire_keypad*) ; 
 int /*<<< orphan*/  get_count_order (int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct nspire_keypad*) ; 
 int matrix_keypad_build_keymap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct input_dev*) ; 
 int /*<<< orphan*/  nspire_keypad_close ; 
 int /*<<< orphan*/  nspire_keypad_irq ; 
 int /*<<< orphan*/  nspire_keypad_open ; 
 scalar_t__ of_property_read_bool (struct device_node const*,char*) ; 
 int of_property_read_u32 (struct device_node const*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nspire_keypad_probe(struct platform_device *pdev)
{
	const struct device_node *of_node = pdev->dev.of_node;
	struct nspire_keypad *keypad;
	struct input_dev *input;
	struct resource *res;
	int irq;
	int error;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -EINVAL;

	keypad = devm_kzalloc(&pdev->dev, sizeof(struct nspire_keypad),
			      GFP_KERNEL);
	if (!keypad) {
		dev_err(&pdev->dev, "failed to allocate keypad memory\n");
		return -ENOMEM;
	}

	keypad->row_shift = get_count_order(KEYPAD_BITMASK_COLS);

	error = of_property_read_u32(of_node, "scan-interval",
				     &keypad->scan_interval);
	if (error) {
		dev_err(&pdev->dev, "failed to get scan-interval\n");
		return error;
	}

	error = of_property_read_u32(of_node, "row-delay",
				     &keypad->row_delay);
	if (error) {
		dev_err(&pdev->dev, "failed to get row-delay\n");
		return error;
	}

	keypad->active_low = of_property_read_bool(of_node, "active-low");

	keypad->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(keypad->clk)) {
		dev_err(&pdev->dev, "unable to get clock\n");
		return PTR_ERR(keypad->clk);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	keypad->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(keypad->reg_base))
		return PTR_ERR(keypad->reg_base);

	keypad->input = input = devm_input_allocate_device(&pdev->dev);
	if (!input) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	input_set_drvdata(input, keypad);

	input->id.bustype = BUS_HOST;
	input->name = "nspire-keypad";
	input->open = nspire_keypad_open;
	input->close = nspire_keypad_close;

	__set_bit(EV_KEY, input->evbit);
	__set_bit(EV_REP, input->evbit);
	input_set_capability(input, EV_MSC, MSC_SCAN);

	error = matrix_keypad_build_keymap(NULL, NULL,
					   KEYPAD_BITMASK_ROWS,
					   KEYPAD_BITMASK_COLS,
					   NULL, input);
	if (error) {
		dev_err(&pdev->dev, "building keymap failed\n");
		return error;
	}

	error = devm_request_irq(&pdev->dev, irq, nspire_keypad_irq, 0,
				 "nspire_keypad", keypad);
	if (error) {
		dev_err(&pdev->dev, "allocate irq %d failed\n", irq);
		return error;
	}

	error = input_register_device(input);
	if (error) {
		dev_err(&pdev->dev,
			"unable to register input device: %d\n", error);
		return error;
	}

	dev_dbg(&pdev->dev,
		"TI-NSPIRE keypad at %pR (scan_interval=%uus, row_delay=%uus%s)\n",
		res, keypad->row_delay, keypad->scan_interval,
		keypad->active_low ? ", active_low" : "");

	return 0;
}