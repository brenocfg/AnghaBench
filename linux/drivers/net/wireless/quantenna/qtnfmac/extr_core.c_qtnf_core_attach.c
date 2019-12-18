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
struct TYPE_2__ {unsigned int ql_proto_ver; unsigned int num_mac; } ;
struct qtnf_bus {int /*<<< orphan*/  fw_state; TYPE_1__ hw_info; int /*<<< orphan*/  event_work; int /*<<< orphan*/  hprio_workqueue; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ERANGE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int QLINK_PROTO_VER ; 
 int /*<<< orphan*/  QTNF_FW_STATE_ACTIVE ; 
 int /*<<< orphan*/  QTNF_FW_STATE_RUNNING ; 
 unsigned int QTNF_MAX_MAC ; 
 int /*<<< orphan*/  WQ_HIGHPRI ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  qtnf_bus_data_rx_start (struct qtnf_bus*) ; 
 int qtnf_cmd_get_hw_info (struct qtnf_bus*) ; 
 int qtnf_cmd_send_init_fw (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_core_detach (struct qtnf_bus*) ; 
 int qtnf_core_mac_attach (struct qtnf_bus*,unsigned int) ; 
 int /*<<< orphan*/  qtnf_event_work_handler ; 
 int /*<<< orphan*/  qtnf_trans_init (struct qtnf_bus*) ; 

int qtnf_core_attach(struct qtnf_bus *bus)
{
	unsigned int i;
	int ret;

	qtnf_trans_init(bus);
	qtnf_bus_data_rx_start(bus);

	bus->workqueue = alloc_ordered_workqueue("QTNF_BUS", 0);
	if (!bus->workqueue) {
		pr_err("failed to alloc main workqueue\n");
		ret = -ENOMEM;
		goto error;
	}

	bus->hprio_workqueue = alloc_workqueue("QTNF_HPRI", WQ_HIGHPRI, 0);
	if (!bus->hprio_workqueue) {
		pr_err("failed to alloc high prio workqueue\n");
		ret = -ENOMEM;
		goto error;
	}

	INIT_WORK(&bus->event_work, qtnf_event_work_handler);

	ret = qtnf_cmd_send_init_fw(bus);
	if (ret) {
		pr_err("failed to init FW: %d\n", ret);
		goto error;
	}

	bus->fw_state = QTNF_FW_STATE_ACTIVE;
	ret = qtnf_cmd_get_hw_info(bus);
	if (ret) {
		pr_err("failed to get HW info: %d\n", ret);
		goto error;
	}

	if (bus->hw_info.ql_proto_ver != QLINK_PROTO_VER) {
		pr_err("qlink version mismatch %u != %u\n",
		       QLINK_PROTO_VER, bus->hw_info.ql_proto_ver);
		ret = -EPROTONOSUPPORT;
		goto error;
	}

	if (bus->hw_info.num_mac > QTNF_MAX_MAC) {
		pr_err("no support for number of MACs=%u\n",
		       bus->hw_info.num_mac);
		ret = -ERANGE;
		goto error;
	}

	for (i = 0; i < bus->hw_info.num_mac; i++) {
		ret = qtnf_core_mac_attach(bus, i);

		if (ret) {
			pr_err("MAC%u: attach failed: %d\n", i, ret);
			goto error;
		}
	}

	bus->fw_state = QTNF_FW_STATE_RUNNING;
	return 0;

error:
	qtnf_core_detach(bus);
	return ret;
}