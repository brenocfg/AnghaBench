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
struct lbs_private {int wep_tx_key; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_set_wep {void* action; void* keyindex; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_SET_WEP ; 
 int CMD_ACT_REMOVE ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_set_wep*) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_set_wep*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_remove_wep_keys(struct lbs_private *priv)
{
	struct cmd_ds_802_11_set_wep cmd;
	int ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.keyindex = cpu_to_le16(priv->wep_tx_key);
	cmd.action = cpu_to_le16(CMD_ACT_REMOVE);

	ret = lbs_cmd_with_response(priv, CMD_802_11_SET_WEP, &cmd);

	return ret;
}