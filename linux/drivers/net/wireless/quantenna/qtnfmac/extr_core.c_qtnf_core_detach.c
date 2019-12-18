#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qtnf_bus {int /*<<< orphan*/ * hprio_workqueue; int /*<<< orphan*/ * workqueue; int /*<<< orphan*/  fw_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  QTNF_FW_STATE_DETACHED ; 
 unsigned int QTNF_MAX_MAC ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtnf_bus_data_rx_stop (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_cmd_send_deinit_fw (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_core_mac_detach (struct qtnf_bus*,unsigned int) ; 
 scalar_t__ qtnf_fw_is_up (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_trans_free (struct qtnf_bus*) ; 

void qtnf_core_detach(struct qtnf_bus *bus)
{
	unsigned int macid;

	qtnf_bus_data_rx_stop(bus);

	for (macid = 0; macid < QTNF_MAX_MAC; macid++)
		qtnf_core_mac_detach(bus, macid);

	if (qtnf_fw_is_up(bus))
		qtnf_cmd_send_deinit_fw(bus);

	bus->fw_state = QTNF_FW_STATE_DETACHED;

	if (bus->workqueue) {
		flush_workqueue(bus->workqueue);
		destroy_workqueue(bus->workqueue);
		bus->workqueue = NULL;
	}

	if (bus->hprio_workqueue) {
		flush_workqueue(bus->hprio_workqueue);
		destroy_workqueue(bus->hprio_workqueue);
		bus->hprio_workqueue = NULL;
	}

	qtnf_trans_free(bus);
}