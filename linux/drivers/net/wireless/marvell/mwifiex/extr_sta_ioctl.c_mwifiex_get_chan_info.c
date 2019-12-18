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
struct mwifiex_private {int dummy; } ;
struct mwifiex_channel_band {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_ACT_GEN_GET ; 
 int /*<<< orphan*/  HostCmd_CMD_STA_CONFIGURE ; 
 int /*<<< orphan*/  MWIFIEX_SYNC_CMD ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_channel_band*,int /*<<< orphan*/ ) ; 

int mwifiex_get_chan_info(struct mwifiex_private *priv,
			  struct mwifiex_channel_band *channel_band)
{
	int status = 0;

	status = mwifiex_send_cmd(priv, HostCmd_CMD_STA_CONFIGURE,
				  HostCmd_ACT_GEN_GET, 0, channel_band,
				  MWIFIEX_SYNC_CMD);

	return status;
}