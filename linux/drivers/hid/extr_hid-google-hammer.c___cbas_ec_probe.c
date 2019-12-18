#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; TYPE_1__ id; } ;
struct cros_ec_device {int /*<<< orphan*/  event_notifier; } ;
struct TYPE_10__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_9__ {int base_present; TYPE_6__ notifier; TYPE_2__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_5__ cbas_ec ; 
 int /*<<< orphan*/  cbas_ec_notify ; 
 int cbas_ec_query_base (struct cros_ec_device*,int,int*) ; 
 int /*<<< orphan*/  cbas_ec_set_input (struct input_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct cros_ec_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_2__*,int) ; 
 struct input_dev* devm_input_allocate_device (TYPE_2__*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_switch (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __cbas_ec_probe(struct platform_device *pdev)
{
	struct cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	struct input_dev *input;
	bool base_supported;
	int error;

	error = cbas_ec_query_base(ec, false, &base_supported);
	if (error)
		return error;

	if (!base_supported)
		return -ENXIO;

	input = devm_input_allocate_device(&pdev->dev);
	if (!input)
		return -ENOMEM;

	input->name = "Whiskers Tablet Mode Switch";
	input->id.bustype = BUS_HOST;

	input_set_capability(input, EV_SW, SW_TABLET_MODE);

	error = input_register_device(input);
	if (error) {
		dev_err(&pdev->dev, "cannot register input device: %d\n",
			error);
		return error;
	}

	/* Seed the state */
	error = cbas_ec_query_base(ec, true, &cbas_ec.base_present);
	if (error) {
		dev_err(&pdev->dev, "cannot query base state: %d\n", error);
		return error;
	}

	input_report_switch(input, SW_TABLET_MODE, !cbas_ec.base_present);

	cbas_ec_set_input(input);

	cbas_ec.dev = &pdev->dev;
	cbas_ec.notifier.notifier_call = cbas_ec_notify;
	error = blocking_notifier_chain_register(&ec->event_notifier,
						 &cbas_ec.notifier);
	if (error) {
		dev_err(&pdev->dev, "cannot register notifier: %d\n", error);
		cbas_ec_set_input(NULL);
		return error;
	}

	device_init_wakeup(&pdev->dev, true);
	return 0;
}