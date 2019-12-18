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
struct at76_priv {TYPE_1__* hw; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 unsigned long CMD_COMPLETION_TIMEOUT ; 
 int CMD_STATUS_IDLE ; 
 int CMD_STATUS_IN_PROGRESS ; 
 int /*<<< orphan*/  DBG_WAIT_COMPLETE ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int at76_get_cmd_status (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  at76_get_cmd_status_string (int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at76_wait_completion(struct at76_priv *priv, int cmd)
{
	int status = 0;
	unsigned long timeout = jiffies + CMD_COMPLETION_TIMEOUT;

	do {
		status = at76_get_cmd_status(priv->udev, cmd);
		if (status < 0) {
			wiphy_err(priv->hw->wiphy,
				  "at76_get_cmd_status failed: %d\n",
				  status);
			break;
		}

		at76_dbg(DBG_WAIT_COMPLETE,
			 "%s: Waiting on cmd %d, status = %d (%s)",
			 wiphy_name(priv->hw->wiphy), cmd, status,
			 at76_get_cmd_status_string(status));

		if (status != CMD_STATUS_IN_PROGRESS
		    && status != CMD_STATUS_IDLE)
			break;

		schedule_timeout_interruptible(HZ / 10);	/* 100 ms */
		if (time_after(jiffies, timeout)) {
			wiphy_err(priv->hw->wiphy,
				  "completion timeout for command %d\n", cmd);
			status = -ETIMEDOUT;
			break;
		}
	} while (1);

	return status;
}