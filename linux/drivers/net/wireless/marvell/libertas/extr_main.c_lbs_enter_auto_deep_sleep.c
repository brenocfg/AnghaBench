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
struct lbs_private {int is_auto_deep_sleep_enabled; int wakeup_dev_required; int auto_deep_sleep_timeout; int /*<<< orphan*/  auto_deepsleep_timer; scalar_t__ is_deep_sleep; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

int lbs_enter_auto_deep_sleep(struct lbs_private *priv)
{
	priv->is_auto_deep_sleep_enabled = 1;
	if (priv->is_deep_sleep)
		priv->wakeup_dev_required = 1;
	mod_timer(&priv->auto_deepsleep_timer ,
			jiffies + (priv->auto_deep_sleep_timeout * HZ)/1000);

	return 0;
}