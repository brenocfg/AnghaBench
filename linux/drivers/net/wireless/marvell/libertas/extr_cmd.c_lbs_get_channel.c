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
struct lbs_private {int dummy; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_rf_channel {int /*<<< orphan*/  channel; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_RF_CHANNEL ; 
 int CMD_OPT_802_11_RF_CHANNEL_GET ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_rf_channel*) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_rf_channel*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_get_channel(struct lbs_private *priv)
{
	struct cmd_ds_802_11_rf_channel cmd;
	int ret = 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_OPT_802_11_RF_CHANNEL_GET);

	ret = lbs_cmd_with_response(priv, CMD_802_11_RF_CHANNEL, &cmd);
	if (ret)
		goto out;

	ret = le16_to_cpu(cmd.channel);
	lbs_deb_cmd("current radio channel is %d\n", ret);

out:
	return ret;
}