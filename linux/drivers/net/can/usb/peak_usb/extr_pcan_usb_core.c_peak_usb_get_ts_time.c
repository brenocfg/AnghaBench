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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct peak_time_ref {scalar_t__ ts_dev_2; int /*<<< orphan*/  tv_host_0; TYPE_1__* adapter; scalar_t__ ts_total; int /*<<< orphan*/  tv_host; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int ts_used_bits; int us_per_ts_scale; int us_per_ts_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 

void peak_usb_get_ts_time(struct peak_time_ref *time_ref, u32 ts, ktime_t *time)
{
	/* protect from getting time before setting now */
	if (ktime_to_ns(time_ref->tv_host)) {
		u64 delta_us;

		delta_us = ts - time_ref->ts_dev_2;
		if (ts < time_ref->ts_dev_2)
			delta_us &= (1 << time_ref->adapter->ts_used_bits) - 1;

		delta_us += time_ref->ts_total;

		delta_us *= time_ref->adapter->us_per_ts_scale;
		delta_us >>= time_ref->adapter->us_per_ts_shift;

		*time = ktime_add_us(time_ref->tv_host_0, delta_us);
	} else {
		*time = ktime_get();
	}
}