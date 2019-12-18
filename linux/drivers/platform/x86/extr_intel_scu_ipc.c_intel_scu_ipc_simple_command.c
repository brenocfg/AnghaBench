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
struct intel_scu_ipc_dev {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int intel_scu_ipc_check_status (struct intel_scu_ipc_dev*) ; 
 int /*<<< orphan*/  ipc_command (struct intel_scu_ipc_dev*,int) ; 
 struct intel_scu_ipc_dev ipcdev ; 
 int /*<<< orphan*/  ipclock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int intel_scu_ipc_simple_command(int cmd, int sub)
{
	struct intel_scu_ipc_dev *scu = &ipcdev;
	int err;

	mutex_lock(&ipclock);
	if (scu->dev == NULL) {
		mutex_unlock(&ipclock);
		return -ENODEV;
	}
	ipc_command(scu, sub << 12 | cmd);
	err = intel_scu_ipc_check_status(scu);
	mutex_unlock(&ipclock);
	return err;
}