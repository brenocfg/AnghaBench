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
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_CLEAR_ALL ; 
 int /*<<< orphan*/  be_clear_error (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int be_cmd_fw_init (struct be_adapter*) ; 
 int be_cmd_reset_function (struct be_adapter*) ; 
 int be_fw_wait_ready (struct be_adapter*) ; 
 int /*<<< orphan*/  be_intr_set (struct be_adapter*,int) ; 
 scalar_t__ be_reset_required (struct be_adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int be_func_init(struct be_adapter *adapter)
{
	int status;

	status = be_fw_wait_ready(adapter);
	if (status)
		return status;

	/* FW is now ready; clear errors to allow cmds/doorbell */
	be_clear_error(adapter, BE_CLEAR_ALL);

	if (be_reset_required(adapter)) {
		status = be_cmd_reset_function(adapter);
		if (status)
			return status;

		/* Wait for interrupts to quiesce after an FLR */
		msleep(100);
	}

	/* Tell FW we're ready to fire cmds */
	status = be_cmd_fw_init(adapter);
	if (status)
		return status;

	/* Allow interrupts for other ULPs running on NIC function */
	be_intr_set(adapter, true);

	return 0;
}