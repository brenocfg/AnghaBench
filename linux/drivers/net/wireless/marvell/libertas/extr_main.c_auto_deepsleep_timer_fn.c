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
struct lbs_private {scalar_t__ connect_status; int auto_deep_sleep_timeout; int /*<<< orphan*/  auto_deepsleep_timer; int /*<<< orphan*/  wakeup_dev_required; scalar_t__ is_auto_deep_sleep_enabled; scalar_t__ is_activity_detected; } ;
struct cmd_header {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_DEEP_SLEEP ; 
 int HZ ; 
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  auto_deepsleep_timer ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct lbs_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lbs_cmd_async (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_header*,int) ; 
 int /*<<< orphan*/  lbs_deb_main (char*) ; 
 int /*<<< orphan*/  memset (struct cmd_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct lbs_private* priv ; 

__attribute__((used)) static void auto_deepsleep_timer_fn(struct timer_list *t)
{
	struct lbs_private *priv = from_timer(priv, t, auto_deepsleep_timer);

	if (priv->is_activity_detected) {
		priv->is_activity_detected = 0;
	} else {
		if (priv->is_auto_deep_sleep_enabled &&
		    (!priv->wakeup_dev_required) &&
		    (priv->connect_status != LBS_CONNECTED)) {
			struct cmd_header cmd;

			lbs_deb_main("Entering auto deep sleep mode...\n");
			memset(&cmd, 0, sizeof(cmd));
			cmd.size = cpu_to_le16(sizeof(cmd));
			lbs_cmd_async(priv, CMD_802_11_DEEP_SLEEP, &cmd,
					sizeof(cmd));
		}
	}
	mod_timer(&priv->auto_deepsleep_timer , jiffies +
				(priv->auto_deep_sleep_timeout * HZ)/1000);
}