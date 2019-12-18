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
struct ptp_clock {int defunct; int /*<<< orphan*/  clock; int /*<<< orphan*/  devid; scalar_t__ pps_source; scalar_t__ kworker; int /*<<< orphan*/  aux_work; int /*<<< orphan*/  tsev_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_destroy_worker (scalar_t__) ; 
 int /*<<< orphan*/  posix_clock_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pps_unregister_source (scalar_t__) ; 
 int /*<<< orphan*/  ptp_class ; 
 int /*<<< orphan*/  ptp_cleanup_pin_groups (struct ptp_clock*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int ptp_clock_unregister(struct ptp_clock *ptp)
{
	ptp->defunct = 1;
	wake_up_interruptible(&ptp->tsev_wq);

	if (ptp->kworker) {
		kthread_cancel_delayed_work_sync(&ptp->aux_work);
		kthread_destroy_worker(ptp->kworker);
	}

	/* Release the clock's resources. */
	if (ptp->pps_source)
		pps_unregister_source(ptp->pps_source);

	device_destroy(ptp_class, ptp->devid);
	ptp_cleanup_pin_groups(ptp);

	posix_clock_unregister(&ptp->clock);
	return 0;
}