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
struct ipw_priv {int /*<<< orphan*/  scan_event; scalar_t__ user_requested_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void handle_scan_event(struct ipw_priv *priv)
{
	/* Only userspace-requested scan completion events go out immediately */
	if (!priv->user_requested_scan) {
		schedule_delayed_work(&priv->scan_event,
				      round_jiffies_relative(msecs_to_jiffies(4000)));
	} else {
		priv->user_requested_scan = 0;
		mod_delayed_work(system_wq, &priv->scan_event, 0);
	}
}