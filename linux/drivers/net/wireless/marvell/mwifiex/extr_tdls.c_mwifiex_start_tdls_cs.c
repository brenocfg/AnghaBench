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
typedef  void* u8 ;
struct mwifiex_tdls_init_cs_params {int /*<<< orphan*/  periodicity; int /*<<< orphan*/  reg_class; void* switch_timeout; void* switch_time; void* band; void* second_chan_offset; void* primary_chan; int /*<<< orphan*/  peer_mac; } ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT_TDLS_CS_INIT ; 
 int /*<<< orphan*/  HostCmd_CMD_TDLS_CONFIG ; 
 int /*<<< orphan*/  MWIFIEX_DEF_CS_PERIODICITY ; 
 int /*<<< orphan*/  MWIFIEX_DEF_CS_REG_CLASS ; 
 int /*<<< orphan*/  MWIFIEX_DEF_CS_TIME ; 
 int /*<<< orphan*/  MWIFIEX_DEF_CS_TIMEOUT ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,void* const*) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_tdls_init_cs_params*,int) ; 

int mwifiex_start_tdls_cs(struct mwifiex_private *priv, const u8 *peer_mac,
			  u8 primary_chan, u8 second_chan_offset, u8 band)
{
	struct mwifiex_tdls_init_cs_params start_tdls_cs_params;

	ether_addr_copy(start_tdls_cs_params.peer_mac, peer_mac);
	start_tdls_cs_params.primary_chan = primary_chan;
	start_tdls_cs_params.second_chan_offset = second_chan_offset;
	start_tdls_cs_params.band = band;

	start_tdls_cs_params.switch_time = cpu_to_le16(MWIFIEX_DEF_CS_TIME);
	start_tdls_cs_params.switch_timeout =
					cpu_to_le16(MWIFIEX_DEF_CS_TIMEOUT);
	start_tdls_cs_params.reg_class = MWIFIEX_DEF_CS_REG_CLASS;
	start_tdls_cs_params.periodicity = MWIFIEX_DEF_CS_PERIODICITY;

	return mwifiex_send_cmd(priv, HostCmd_CMD_TDLS_CONFIG,
				ACT_TDLS_CS_INIT, 0,
				&start_tdls_cs_params, true);
}