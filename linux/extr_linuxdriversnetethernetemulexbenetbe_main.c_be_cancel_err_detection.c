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
struct be_error_recovery {int /*<<< orphan*/  err_detection_work; } ;
struct be_adapter {int flags; struct be_error_recovery error_recovery; } ;

/* Variables and functions */
 int BE_FLAGS_ERR_DETECTION_SCHEDULED ; 
 int /*<<< orphan*/  be_err_recovery_workq ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void be_cancel_err_detection(struct be_adapter *adapter)
{
	struct be_error_recovery *err_rec = &adapter->error_recovery;

	if (!be_err_recovery_workq)
		return;

	if (adapter->flags & BE_FLAGS_ERR_DETECTION_SCHEDULED) {
		cancel_delayed_work_sync(&err_rec->err_detection_work);
		adapter->flags &= ~BE_FLAGS_ERR_DETECTION_SCHEDULED;
	}
}