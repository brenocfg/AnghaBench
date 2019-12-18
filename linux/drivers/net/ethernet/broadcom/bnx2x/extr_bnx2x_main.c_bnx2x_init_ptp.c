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
struct bnx2x {int timecounter_init_done; int /*<<< orphan*/  cyclecounter; int /*<<< orphan*/  timecounter; int /*<<< orphan*/  ptp_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_PTP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bnx2x_configure_ptp (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_init_cyclecounter (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_ptp_task ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bnx2x_init_ptp(struct bnx2x *bp)
{
	int rc;

	/* Configure PTP in HW */
	rc = bnx2x_configure_ptp(bp);
	if (rc) {
		BNX2X_ERR("Stopping PTP initialization\n");
		return;
	}

	/* Init work queue for Tx timestamping */
	INIT_WORK(&bp->ptp_task, bnx2x_ptp_task);

	/* Init cyclecounter and timecounter. This is done only in the first
	 * load. If done in every load, PTP application will fail when doing
	 * unload / load (e.g. MTU change) while it is running.
	 */
	if (!bp->timecounter_init_done) {
		bnx2x_init_cyclecounter(bp);
		timecounter_init(&bp->timecounter, &bp->cyclecounter,
				 ktime_to_ns(ktime_get_real()));
		bp->timecounter_init_done = 1;
	}

	DP(BNX2X_MSG_PTP, "PTP initialization ended successfully\n");
}