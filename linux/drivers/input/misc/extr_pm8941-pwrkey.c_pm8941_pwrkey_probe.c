#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int /*<<< orphan*/  notifier_call; } ;
struct pm8941_pwrkey {int baseaddr; scalar_t__ irq; int code; TYPE_1__ reboot_notifier; TYPE_4__* input; TYPE_2__* data; void* regmap; int /*<<< orphan*/  revision; TYPE_3__* dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct TYPE_16__ {char* name; char* phys; } ;
struct TYPE_14__ {int pull_up_bit; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int KEY_POWER ; 
 int PON_DBC_CTL ; 
 int PON_DBC_DELAY_MASK ; 
 int PON_PULL_CTL ; 
 int PON_REV2 ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 void* dev_get_regmap (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_3__*,int) ; 
 TYPE_4__* devm_input_allocate_device (TYPE_3__*) ; 
 struct pm8941_pwrkey* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pm8941_pwrkey*) ; 
 int ilog2 (int) ; 
 int input_register_device (TYPE_4__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* of_device_get_match_data (TYPE_3__*) ; 
 int of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pm8941_pwrkey*) ; 
 int /*<<< orphan*/  pm8941_pwrkey_irq ; 
 int /*<<< orphan*/  pm8941_reboot_notify ; 
 int register_reboot_notifier (TYPE_1__*) ; 
 int regmap_read (void*,int,int /*<<< orphan*/ *) ; 
 int regmap_update_bits (void*,int,int,int) ; 

__attribute__((used)) static int pm8941_pwrkey_probe(struct platform_device *pdev)
{
	struct pm8941_pwrkey *pwrkey;
	bool pull_up;
	struct device *parent;
	u32 req_delay;
	int error;

	if (of_property_read_u32(pdev->dev.of_node, "debounce", &req_delay))
		req_delay = 15625;

	if (req_delay > 2000000 || req_delay == 0) {
		dev_err(&pdev->dev, "invalid debounce time: %u\n", req_delay);
		return -EINVAL;
	}

	pull_up = of_property_read_bool(pdev->dev.of_node, "bias-pull-up");

	pwrkey = devm_kzalloc(&pdev->dev, sizeof(*pwrkey), GFP_KERNEL);
	if (!pwrkey)
		return -ENOMEM;

	pwrkey->dev = &pdev->dev;
	pwrkey->data = of_device_get_match_data(&pdev->dev);

	parent = pdev->dev.parent;
	pwrkey->regmap = dev_get_regmap(parent, NULL);
	if (!pwrkey->regmap) {
		/*
		 * We failed to get regmap for parent. Let's see if we are
		 * a child of pon node and read regmap and reg from its
		 * parent.
		 */
		pwrkey->regmap = dev_get_regmap(parent->parent, NULL);
		if (!pwrkey->regmap) {
			dev_err(&pdev->dev, "failed to locate regmap\n");
			return -ENODEV;
		}

		error = of_property_read_u32(parent->of_node,
					     "reg", &pwrkey->baseaddr);
	} else {
		error = of_property_read_u32(pdev->dev.of_node, "reg",
					     &pwrkey->baseaddr);
	}
	if (error)
		return error;

	pwrkey->irq = platform_get_irq(pdev, 0);
	if (pwrkey->irq < 0)
		return pwrkey->irq;

	error = regmap_read(pwrkey->regmap, pwrkey->baseaddr + PON_REV2,
			    &pwrkey->revision);
	if (error) {
		dev_err(&pdev->dev, "failed to set debounce: %d\n", error);
		return error;
	}

	error = of_property_read_u32(pdev->dev.of_node, "linux,code",
				     &pwrkey->code);
	if (error) {
		dev_dbg(&pdev->dev,
			"no linux,code assuming power (%d)\n", error);
		pwrkey->code = KEY_POWER;
	}

	pwrkey->input = devm_input_allocate_device(&pdev->dev);
	if (!pwrkey->input) {
		dev_dbg(&pdev->dev, "unable to allocate input device\n");
		return -ENOMEM;
	}

	input_set_capability(pwrkey->input, EV_KEY, pwrkey->code);

	pwrkey->input->name = "pm8941_pwrkey";
	pwrkey->input->phys = "pm8941_pwrkey/input0";

	req_delay = (req_delay << 6) / USEC_PER_SEC;
	req_delay = ilog2(req_delay);

	error = regmap_update_bits(pwrkey->regmap,
				   pwrkey->baseaddr + PON_DBC_CTL,
				   PON_DBC_DELAY_MASK,
				   req_delay);
	if (error) {
		dev_err(&pdev->dev, "failed to set debounce: %d\n", error);
		return error;
	}

	error = regmap_update_bits(pwrkey->regmap,
				   pwrkey->baseaddr + PON_PULL_CTL,
				   pwrkey->data->pull_up_bit,
				   pull_up ? pwrkey->data->pull_up_bit : 0);
	if (error) {
		dev_err(&pdev->dev, "failed to set pull: %d\n", error);
		return error;
	}

	error = devm_request_threaded_irq(&pdev->dev, pwrkey->irq,
					  NULL, pm8941_pwrkey_irq,
					  IRQF_ONESHOT,
					  "pm8941_pwrkey", pwrkey);
	if (error) {
		dev_err(&pdev->dev, "failed requesting IRQ: %d\n", error);
		return error;
	}

	error = input_register_device(pwrkey->input);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device: %d\n",
			error);
		return error;
	}

	pwrkey->reboot_notifier.notifier_call = pm8941_reboot_notify,
	error = register_reboot_notifier(&pwrkey->reboot_notifier);
	if (error) {
		dev_err(&pdev->dev, "failed to register reboot notifier: %d\n",
			error);
		return error;
	}

	platform_set_drvdata(pdev, pwrkey);
	device_init_wakeup(&pdev->dev, 1);

	return 0;
}