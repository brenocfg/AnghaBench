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
struct lbs_private {int /*<<< orphan*/  auto_deepsleep_timer; scalar_t__ auto_deep_sleep_timeout; scalar_t__ is_auto_deep_sleep_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

int lbs_exit_auto_deep_sleep(struct lbs_private *priv)
{
	priv->is_auto_deep_sleep_enabled = 0;
	priv->auto_deep_sleep_timeout = 0;
	del_timer(&priv->auto_deepsleep_timer);

	return 0;
}