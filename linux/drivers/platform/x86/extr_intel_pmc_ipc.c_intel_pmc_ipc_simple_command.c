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
struct TYPE_2__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int IPC_CMD_SUBCMD ; 
 int intel_pmc_ipc_check_status () ; 
 int /*<<< orphan*/  ipc_send_command (int) ; 
 TYPE_1__ ipcdev ; 
 int /*<<< orphan*/  ipclock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int intel_pmc_ipc_simple_command(int cmd, int sub)
{
	int ret;

	mutex_lock(&ipclock);
	if (ipcdev.dev == NULL) {
		mutex_unlock(&ipclock);
		return -ENODEV;
	}
	ipc_send_command(sub << IPC_CMD_SUBCMD | cmd);
	ret = intel_pmc_ipc_check_status();
	mutex_unlock(&ipclock);

	return ret;
}