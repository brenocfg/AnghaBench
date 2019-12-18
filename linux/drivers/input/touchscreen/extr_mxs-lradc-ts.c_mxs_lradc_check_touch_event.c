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
struct mxs_lradc_ts {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LRADC_STATUS ; 
 int LRADC_STATUS_TOUCH_DETECT_RAW ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static bool mxs_lradc_check_touch_event(struct mxs_lradc_ts *ts)
{
	return !!(readl(ts->base + LRADC_STATUS) &
					LRADC_STATUS_TOUCH_DETECT_RAW);
}