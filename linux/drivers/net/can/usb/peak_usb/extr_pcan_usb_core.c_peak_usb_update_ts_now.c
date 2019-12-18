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
typedef  int u32 ;
struct peak_time_ref {int ts_dev_2; int ts_dev_1; int ts_total; TYPE_1__* adapter; int /*<<< orphan*/  tv_host; } ;
struct TYPE_2__ {int ts_used_bits; } ;

/* Variables and functions */
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 

void peak_usb_update_ts_now(struct peak_time_ref *time_ref, u32 ts_now)
{
	time_ref->ts_dev_2 = ts_now;

	/* should wait at least two passes before computing */
	if (ktime_to_ns(time_ref->tv_host) > 0) {
		u32 delta_ts = time_ref->ts_dev_2 - time_ref->ts_dev_1;

		if (time_ref->ts_dev_2 < time_ref->ts_dev_1)
			delta_ts &= (1 << time_ref->adapter->ts_used_bits) - 1;

		time_ref->ts_total += delta_ts;
	}
}