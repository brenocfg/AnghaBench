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
struct hv_util_service {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adj_time_work ; 
 TYPE_1__ host_ts ; 
 int /*<<< orphan*/ * hv_ptp_clock ; 
 int /*<<< orphan*/  hv_set_host_time ; 
 int /*<<< orphan*/  hyperv_cs ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ptp_clock_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptp_hyperv_info ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hv_timesync_init(struct hv_util_service *srv)
{
	/* TimeSync requires Hyper-V clocksource. */
	if (!hyperv_cs)
		return -ENODEV;

	spin_lock_init(&host_ts.lock);

	INIT_WORK(&adj_time_work, hv_set_host_time);

	/*
	 * ptp_clock_register() returns NULL when CONFIG_PTP_1588_CLOCK is
	 * disabled but the driver is still useful without the PTP device
	 * as it still handles the ICTIMESYNCFLAG_SYNC case.
	 */
	hv_ptp_clock = ptp_clock_register(&ptp_hyperv_info, NULL);
	if (IS_ERR_OR_NULL(hv_ptp_clock)) {
		pr_err("cannot register PTP clock: %ld\n",
		       PTR_ERR(hv_ptp_clock));
		hv_ptp_clock = NULL;
	}

	return 0;
}