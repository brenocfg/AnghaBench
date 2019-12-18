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
struct timer_list {int dummy; } ;
struct r8192_priv {int polling_timer_on; int /*<<< orphan*/  gpio_polling_timer; int /*<<< orphan*/  gpio_change_rf_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTLLIB_WATCH_DOG_TIME ; 
 struct r8192_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_polling_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct r8192_priv* priv ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rtl92e_check_rfctrl_gpio_timer(struct timer_list *t)
{
	struct r8192_priv *priv = from_timer(priv, t, gpio_polling_timer);

	priv->polling_timer_on = 1;

	schedule_delayed_work(&priv->gpio_change_rf_wq, 0);

	mod_timer(&priv->gpio_polling_timer, jiffies +
		  msecs_to_jiffies(RTLLIB_WATCH_DOG_TIME));
}