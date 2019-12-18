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
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct uwb_drp_backoff_win {int window; int can_reserve_extra_mases; int n; int /*<<< orphan*/  timer; scalar_t__ total_expired; } ;
struct uwb_rc {TYPE_1__ uwb_dev; struct uwb_drp_backoff_win bow; } ;

/* Variables and functions */
 int UWB_DRP_BACKOFF_WIN_MAX ; 
 unsigned int UWB_SUPERFRAME_LENGTH_US ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int prandom_u32 () ; 
 scalar_t__ usecs_to_jiffies (unsigned int) ; 

void uwb_rsv_backoff_win_increment(struct uwb_rc *rc)
{
	struct uwb_drp_backoff_win *bow = &rc->bow;
	struct device *dev = &rc->uwb_dev.dev;
	unsigned timeout_us;

	dev_dbg(dev, "backoff_win_increment: window=%d\n", bow->window);

	bow->can_reserve_extra_mases = false;

	if((bow->window << 1) == UWB_DRP_BACKOFF_WIN_MAX)
		return;

	bow->window <<= 1;
	bow->n = prandom_u32() & (bow->window - 1);
	dev_dbg(dev, "new_window=%d, n=%d\n", bow->window, bow->n);

	/* reset the timer associated variables */
	timeout_us = bow->n * UWB_SUPERFRAME_LENGTH_US;
	bow->total_expired = 0;
	mod_timer(&bow->timer, jiffies + usecs_to_jiffies(timeout_us));
}