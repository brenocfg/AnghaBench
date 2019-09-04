#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct ehea_adapter {int /*<<< orphan*/  list; TYPE_2__* neq; int /*<<< orphan*/  neq_tasklet; int /*<<< orphan*/ ** port; } ;
struct TYPE_3__ {int /*<<< orphan*/  ist1; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;

/* Variables and functions */
 int EHEA_MAX_PORTS ; 
 int /*<<< orphan*/  ehea_destroy_eq (TYPE_2__*) ; 
 int /*<<< orphan*/  ehea_remove_adapter_mr (struct ehea_adapter*) ; 
 int /*<<< orphan*/  ehea_remove_device_sysfs (struct platform_device*) ; 
 int /*<<< orphan*/  ehea_shutdown_single_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehea_update_firmware_handles () ; 
 int /*<<< orphan*/  ibmebus_free_irq (int /*<<< orphan*/ ,struct ehea_adapter*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct ehea_adapter* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehea_remove(struct platform_device *dev)
{
	struct ehea_adapter *adapter = platform_get_drvdata(dev);
	int i;

	for (i = 0; i < EHEA_MAX_PORTS; i++)
		if (adapter->port[i]) {
			ehea_shutdown_single_port(adapter->port[i]);
			adapter->port[i] = NULL;
		}

	ehea_remove_device_sysfs(dev);

	ibmebus_free_irq(adapter->neq->attr.ist1, adapter);
	tasklet_kill(&adapter->neq_tasklet);

	ehea_destroy_eq(adapter->neq);
	ehea_remove_adapter_mr(adapter);
	list_del(&adapter->list);

	ehea_update_firmware_handles();

	return 0;
}