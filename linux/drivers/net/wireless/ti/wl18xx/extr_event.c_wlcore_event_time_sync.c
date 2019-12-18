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
typedef  int u32 ;
typedef  int u16 ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wl1271_info (char*,int,int) ; 

__attribute__((used)) static void wlcore_event_time_sync(struct wl1271 *wl,
				   u16 tsf_high_msb, u16 tsf_high_lsb,
				   u16 tsf_low_msb, u16 tsf_low_lsb)
{
	u32 clock_low;
	u32 clock_high;

	clock_high = (tsf_high_msb << 16) | tsf_high_lsb;
	clock_low = (tsf_low_msb << 16) | tsf_low_lsb;

	wl1271_info("TIME_SYNC_EVENT_ID: clock_high %u, clock low %u",
		    clock_high, clock_low);
}