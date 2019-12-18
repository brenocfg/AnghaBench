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
struct cmd_ds_802_11_rf_tx_power {void* curlevel; void* action; TYPE_1__ hdr; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_RF_TX_POWER ; 
 int CMD_ACT_SET ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_rf_tx_power*) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,int) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_rf_tx_power*,int /*<<< orphan*/ ,int) ; 

int lbs_set_tx_power(struct lbs_private *priv, s16 dbm)
{
	struct cmd_ds_802_11_rf_tx_power cmd;
	int ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.curlevel = cpu_to_le16(dbm);

	lbs_deb_cmd("SET_RF_TX_POWER: %d dBm\n", dbm);

	ret = lbs_cmd_with_response(priv, CMD_802_11_RF_TX_POWER, &cmd);

	return ret;
}