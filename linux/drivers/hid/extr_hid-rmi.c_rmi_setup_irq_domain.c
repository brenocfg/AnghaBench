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
struct rmi_data {scalar_t__ rmi_irq; int /*<<< orphan*/  domain; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;
struct hid_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int devm_add_action_or_reset (TYPE_1__*,int /*<<< orphan*/ *,struct rmi_data*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct rmi_data* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_create_linear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct rmi_data*) ; 
 int /*<<< orphan*/  rmi_irq_ops ; 
 int /*<<< orphan*/  rmi_irq_teardown ; 

__attribute__((used)) static int rmi_setup_irq_domain(struct hid_device *hdev)
{
	struct rmi_data *hdata = hid_get_drvdata(hdev);
	int ret;

	hdata->domain = irq_domain_create_linear(hdev->dev.fwnode, 1,
						 &rmi_irq_ops, hdata);
	if (!hdata->domain)
		return -ENOMEM;

	ret = devm_add_action_or_reset(&hdev->dev, &rmi_irq_teardown, hdata);
	if (ret)
		return ret;

	hdata->rmi_irq = irq_create_mapping(hdata->domain, 0);
	if (hdata->rmi_irq <= 0) {
		hid_err(hdev, "Can't allocate an IRQ\n");
		return hdata->rmi_irq < 0 ? hdata->rmi_irq : -ENXIO;
	}

	return 0;
}