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
typedef  int /*<<< orphan*/  u16 ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_ds_wakeup_reason {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_ACT_GEN_GET ; 
 int /*<<< orphan*/  HostCmd_CMD_HS_WAKEUP_REASON ; 
 int MWIFIEX_SYNC_CMD ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_ds_wakeup_reason*,int) ; 

int mwifiex_get_wakeup_reason(struct mwifiex_private *priv, u16 action,
			      int cmd_type,
			      struct mwifiex_ds_wakeup_reason *wakeup_reason)
{
	int status = 0;

	status = mwifiex_send_cmd(priv, HostCmd_CMD_HS_WAKEUP_REASON,
				  HostCmd_ACT_GEN_GET, 0, wakeup_reason,
				  cmd_type == MWIFIEX_SYNC_CMD);

	return status;
}