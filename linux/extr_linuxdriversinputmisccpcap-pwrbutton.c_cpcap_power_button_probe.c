#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_4__ dev; } ;
struct cpcap_power_button {TYPE_2__* idev; TYPE_4__* dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_10__ {TYPE_4__* parent; } ;
struct TYPE_11__ {char* name; char* phys; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_4__*,int) ; 
 TYPE_2__* devm_input_allocate_device (TYPE_4__*) ; 
 struct cpcap_power_button* devm_kmalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cpcap_power_button*) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerbutton_irq ; 

__attribute__((used)) static int cpcap_power_button_probe(struct platform_device *pdev)
{
	struct cpcap_power_button *button;
	int irq = platform_get_irq(pdev, 0);
	int err;

	button = devm_kmalloc(&pdev->dev, sizeof(*button), GFP_KERNEL);
	if (!button)
		return -ENOMEM;

	button->idev = devm_input_allocate_device(&pdev->dev);
	if (!button->idev)
		return -ENOMEM;

	button->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!button->regmap)
		return -ENODEV;

	button->dev = &pdev->dev;

	button->idev->name = "cpcap-pwrbutton";
	button->idev->phys = "cpcap-pwrbutton/input0";
	button->idev->dev.parent = button->dev;
	input_set_capability(button->idev, EV_KEY, KEY_POWER);

	err = devm_request_threaded_irq(&pdev->dev, irq, NULL,
		powerbutton_irq, IRQF_ONESHOT, "cpcap_pwrbutton", button);
	if (err < 0) {
		dev_err(&pdev->dev, "IRQ request failed: %d\n", err);
		return err;
	}

	err = input_register_device(button->idev);
	if (err) {
		dev_err(&pdev->dev, "Input register failed: %d\n", err);
		return err;
	}

	device_init_wakeup(&pdev->dev, true);

	return 0;
}