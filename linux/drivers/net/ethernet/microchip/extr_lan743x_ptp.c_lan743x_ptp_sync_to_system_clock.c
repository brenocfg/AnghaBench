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
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_clocktai_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  lan743x_ptp_clock_set (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan743x_ptp_sync_to_system_clock(struct lan743x_adapter *adapter)
{
	struct timespec64 ts;

	ktime_get_clocktai_ts64(&ts);

	lan743x_ptp_clock_set(adapter, ts.tv_sec, ts.tv_nsec, 0);
}