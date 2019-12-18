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
struct st_keyscan {scalar_t__ irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; int /*<<< orphan*/  n_cols; int /*<<< orphan*/  n_rows; struct input_dev* input_dev; } ;
struct resource {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_10__ {TYPE_3__* parent; } ;
struct input_dev {char* phys; TYPE_2__ id; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_3__*,int) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct st_keyscan* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct st_keyscan*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct st_keyscan*) ; 
 int keypad_matrix_key_parse_dt (struct st_keyscan*) ; 
 int /*<<< orphan*/  keyscan_close ; 
 int /*<<< orphan*/  keyscan_isr ; 
 int /*<<< orphan*/  keyscan_open ; 
 int /*<<< orphan*/  keyscan_stop (struct st_keyscan*) ; 
 int matrix_keypad_build_keymap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct input_dev*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct st_keyscan*) ; 

__attribute__((used)) static int keyscan_probe(struct platform_device *pdev)
{
	struct st_keyscan *keypad_data;
	struct input_dev *input_dev;
	struct resource *res;
	int error;

	if (!pdev->dev.of_node) {
		dev_err(&pdev->dev, "no DT data present\n");
		return -EINVAL;
	}

	keypad_data = devm_kzalloc(&pdev->dev, sizeof(*keypad_data),
				   GFP_KERNEL);
	if (!keypad_data)
		return -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!input_dev) {
		dev_err(&pdev->dev, "failed to allocate the input device\n");
		return -ENOMEM;
	}

	input_dev->name = pdev->name;
	input_dev->phys = "keyscan-keys/input0";
	input_dev->dev.parent = &pdev->dev;
	input_dev->open = keyscan_open;
	input_dev->close = keyscan_close;

	input_dev->id.bustype = BUS_HOST;

	keypad_data->input_dev = input_dev;

	error = keypad_matrix_key_parse_dt(keypad_data);
	if (error)
		return error;

	error = matrix_keypad_build_keymap(NULL, NULL,
					   keypad_data->n_rows,
					   keypad_data->n_cols,
					   NULL, input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to build keymap\n");
		return error;
	}

	input_set_drvdata(input_dev, keypad_data);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	keypad_data->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(keypad_data->base))
		return PTR_ERR(keypad_data->base);

	keypad_data->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(keypad_data->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		return PTR_ERR(keypad_data->clk);
	}

	error = clk_enable(keypad_data->clk);
	if (error) {
		dev_err(&pdev->dev, "failed to enable clock\n");
		return error;
	}

	keyscan_stop(keypad_data);

	keypad_data->irq = platform_get_irq(pdev, 0);
	if (keypad_data->irq < 0)
		return -EINVAL;

	error = devm_request_irq(&pdev->dev, keypad_data->irq, keyscan_isr, 0,
				 pdev->name, keypad_data);
	if (error) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		return error;
	}

	error = input_register_device(input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device\n");
		return error;
	}

	platform_set_drvdata(pdev, keypad_data);

	device_set_wakeup_capable(&pdev->dev, 1);

	return 0;
}