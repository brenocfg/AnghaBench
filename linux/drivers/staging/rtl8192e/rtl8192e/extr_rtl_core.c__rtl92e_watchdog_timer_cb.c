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
struct r8192_priv {int /*<<< orphan*/  watch_dog_timer; int /*<<< orphan*/  watch_dog_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTLLIB_WATCH_DOG_TIME ; 
 struct r8192_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct r8192_priv* priv ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watch_dog_timer ; 

__attribute__((used)) static void _rtl92e_watchdog_timer_cb(struct timer_list *t)
{
	struct r8192_priv *priv = from_timer(priv, t, watch_dog_timer);

	schedule_delayed_work(&priv->watch_dog_wq, 0);
	mod_timer(&priv->watch_dog_timer, jiffies +
		  msecs_to_jiffies(RTLLIB_WATCH_DOG_TIME));
}