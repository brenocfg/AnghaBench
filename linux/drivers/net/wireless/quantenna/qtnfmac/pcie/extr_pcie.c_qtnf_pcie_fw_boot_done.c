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
struct qtnf_bus {int /*<<< orphan*/  fw_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  QTNF_FW_STATE_BOOT_DONE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int qtnf_core_attach (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_dbg_mps_show ; 
 int /*<<< orphan*/  qtnf_dbg_msi_show ; 
 int /*<<< orphan*/  qtnf_dbg_shm_stats ; 
 int /*<<< orphan*/  qtnf_debugfs_add_entry (struct qtnf_bus*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_debugfs_init (struct qtnf_bus*,int /*<<< orphan*/ ) ; 

int qtnf_pcie_fw_boot_done(struct qtnf_bus *bus)
{
	int ret;

	bus->fw_state = QTNF_FW_STATE_BOOT_DONE;
	ret = qtnf_core_attach(bus);
	if (ret) {
		pr_err("failed to attach core\n");
	} else {
		qtnf_debugfs_init(bus, DRV_NAME);
		qtnf_debugfs_add_entry(bus, "mps", qtnf_dbg_mps_show);
		qtnf_debugfs_add_entry(bus, "msi_enabled", qtnf_dbg_msi_show);
		qtnf_debugfs_add_entry(bus, "shm_stats", qtnf_dbg_shm_stats);
	}

	return ret;
}