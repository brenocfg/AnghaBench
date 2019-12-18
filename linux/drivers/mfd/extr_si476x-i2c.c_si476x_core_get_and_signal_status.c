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
struct si476x_core {int /*<<< orphan*/  tuning; int /*<<< orphan*/  stc; TYPE_1__* client; int /*<<< orphan*/  command; int /*<<< orphan*/  cts; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SI476X_CTS ; 
 int SI476X_FM_RDS_INT ; 
 int SI476X_STC_INT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int si476x_core_get_status (struct si476x_core*) ; 
 int /*<<< orphan*/  si476x_core_start_rds_drainer_once (struct si476x_core*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void si476x_core_get_and_signal_status(struct si476x_core *core)
{
	int status = si476x_core_get_status(core);
	if (status < 0) {
		dev_err(&core->client->dev, "Failed to get status\n");
		return;
	}

	if (status & SI476X_CTS) {
		/* Unfortunately completions could not be used for
		 * signalling CTS since this flag cannot be cleared
		 * in status byte, and therefore once it becomes true
		 * multiple calls to 'complete' would cause the
		 * commands following the current one to be completed
		 * before they actually are */
		dev_dbg(&core->client->dev, "[interrupt] CTSINT\n");
		atomic_set(&core->cts, 1);
		wake_up(&core->command);
	}

	if (status & SI476X_FM_RDS_INT) {
		dev_dbg(&core->client->dev, "[interrupt] RDSINT\n");
		si476x_core_start_rds_drainer_once(core);
	}

	if (status & SI476X_STC_INT) {
		dev_dbg(&core->client->dev, "[interrupt] STCINT\n");
		atomic_set(&core->stc, 1);
		wake_up(&core->tuning);
	}
}