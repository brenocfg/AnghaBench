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
struct bd70528_rtc {int /*<<< orphan*/  dev; int /*<<< orphan*/  mfd; } ;

/* Variables and functions */
 int BD70528_ELAPSED_STATE_BIT ; 
 int BD70528_WAKE_STATE_BIT ; 
 int BD70528_WDT_STATE_BIT ; 
 int bd70528_set_elapsed_tmr (int /*<<< orphan*/ ,int,int*) ; 
 int bd70528_set_wake (int /*<<< orphan*/ ,int,int*) ; 
 int bd70528_wdt_set (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int bd70528_set_rtc_based_timers(struct bd70528_rtc *r, int new_state,
					int *old_state)
{
	int ret;

	ret = bd70528_wdt_set(r->mfd, new_state & BD70528_WDT_STATE_BIT,
			      old_state);
	if (ret) {
		dev_err(r->dev,
			"Failed to disable WDG for RTC setting (%d)\n", ret);
		return ret;
	}
	ret = bd70528_set_elapsed_tmr(r->mfd,
				      new_state & BD70528_ELAPSED_STATE_BIT,
				      old_state);
	if (ret) {
		dev_err(r->dev,
			"Failed to disable 'elapsed timer' for RTC setting\n");
		return ret;
	}
	ret = bd70528_set_wake(r->mfd, new_state & BD70528_WAKE_STATE_BIT,
			       old_state);
	if (ret) {
		dev_err(r->dev,
			"Failed to disable 'wake timer' for RTC setting\n");
		return ret;
	}

	return ret;
}