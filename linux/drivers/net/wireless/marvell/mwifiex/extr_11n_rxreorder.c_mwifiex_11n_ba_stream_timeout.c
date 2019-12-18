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
typedef  int u16 ;
struct mwifiex_private {int dummy; } ;
struct host_cmd_ds_11n_delba {int /*<<< orphan*/  reason_code; int /*<<< orphan*/  del_ba_param_set; int /*<<< orphan*/  peer_mac_addr; } ;
struct host_cmd_ds_11n_batimeout {scalar_t__ origninator; scalar_t__ tid; int /*<<< orphan*/  peer_mac_addr; } ;

/* Variables and functions */
 int DELBA_INITIATOR_POS ; 
 int DELBA_TID_POS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HostCmd_CMD_11N_DELBA ; 
 int WLAN_REASON_QSTA_TIMEOUT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct host_cmd_ds_11n_delba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct host_cmd_ds_11n_delba*,int) ; 

void mwifiex_11n_ba_stream_timeout(struct mwifiex_private *priv,
				   struct host_cmd_ds_11n_batimeout *event)
{
	struct host_cmd_ds_11n_delba delba;

	memset(&delba, 0, sizeof(struct host_cmd_ds_11n_delba));
	memcpy(delba.peer_mac_addr, event->peer_mac_addr, ETH_ALEN);

	delba.del_ba_param_set |=
		cpu_to_le16((u16) event->tid << DELBA_TID_POS);
	delba.del_ba_param_set |= cpu_to_le16(
		(u16) event->origninator << DELBA_INITIATOR_POS);
	delba.reason_code = cpu_to_le16(WLAN_REASON_QSTA_TIMEOUT);
	mwifiex_send_cmd(priv, HostCmd_CMD_11N_DELBA, 0, 0, &delba, false);
}