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
struct mwifiex_private {int auto_tdls_timer_active; int /*<<< orphan*/  auto_tdls_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_TIMER_10S ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_check_auto_tdls ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mwifiex_setup_auto_tdls_timer(struct mwifiex_private *priv)
{
	timer_setup(&priv->auto_tdls_timer, mwifiex_check_auto_tdls, 0);
	priv->auto_tdls_timer_active = true;
	mod_timer(&priv->auto_tdls_timer,
		  jiffies + msecs_to_jiffies(MWIFIEX_TIMER_10S));
}