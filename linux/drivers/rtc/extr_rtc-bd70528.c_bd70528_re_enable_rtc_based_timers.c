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
struct bd70528_rtc {int dummy; } ;

/* Variables and functions */
 int bd70528_set_rtc_based_timers (struct bd70528_rtc*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bd70528_re_enable_rtc_based_timers(struct bd70528_rtc *r,
					      int old_state)
{
	return bd70528_set_rtc_based_timers(r, old_state, NULL);
}