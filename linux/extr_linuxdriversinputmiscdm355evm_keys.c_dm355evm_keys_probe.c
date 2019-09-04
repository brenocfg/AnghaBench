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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int product; int /*<<< orphan*/  version; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; char* phys; TYPE_1__ id; } ;
struct dm355evm_keys {struct input_dev* input; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_I2C ; 
 int /*<<< orphan*/  DM355EVM_MSP_FIRMREV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct dm355evm_keys* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dm355evm_keys*) ; 
 int /*<<< orphan*/  dm355evm_keys ; 
 int /*<<< orphan*/  dm355evm_keys_irq ; 
 int /*<<< orphan*/  dm355evm_msp_read (int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int sparse_keymap_setup (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm355evm_keys_probe(struct platform_device *pdev)
{
	struct dm355evm_keys	*keys;
	struct input_dev	*input;
	int			irq;
	int			error;

	keys = devm_kzalloc(&pdev->dev, sizeof (*keys), GFP_KERNEL);
	if (!keys)
		return -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	if (!input)
		return -ENOMEM;

	keys->dev = &pdev->dev;
	keys->input = input;

	input->name = "DM355 EVM Controls";
	input->phys = "dm355evm/input0";

	input->id.bustype = BUS_I2C;
	input->id.product = 0x0355;
	input->id.version = dm355evm_msp_read(DM355EVM_MSP_FIRMREV);

	error = sparse_keymap_setup(input, dm355evm_keys, NULL);
	if (error)
		return error;

	/* REVISIT:  flush the event queue? */

	/* set up "threaded IRQ handler" */
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	error = devm_request_threaded_irq(&pdev->dev, irq,
					  NULL, dm355evm_keys_irq,
					  IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					  dev_name(&pdev->dev), keys);
	if (error)
		return error;

	/* register */
	error = input_register_device(input);
	if (error)
		return error;

	return 0;
}