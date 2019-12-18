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
struct cmd_ds_802_11_enable_rsn {void* enable; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_ENABLE_RSN ; 
 int CMD_ACT_SET ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_enable_rsn*) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_enable_rsn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_enable_rsn(struct lbs_private *priv, int enable)
{
	struct cmd_ds_802_11_enable_rsn cmd;
	int ret;

	/*
	 * cmd       2f 00
	 * size      0c 00
	 * sequence  xx xx
	 * result    00 00
	 * action    01 00    ACT_SET
	 * enable    01 00
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.enable = cpu_to_le16(enable);

	ret = lbs_cmd_with_response(priv, CMD_802_11_ENABLE_RSN, &cmd);

	return ret;
}