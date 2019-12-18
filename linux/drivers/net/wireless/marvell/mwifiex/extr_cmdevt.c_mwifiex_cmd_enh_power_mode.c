#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct mwifiex_ps_param {void* mode; void* delay_to_ps; void* adhoc_wake_period; void* local_listen_interval; void* bcn_miss_timeout; void* multiple_dtims; void* null_pkt_interval; } ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct TYPE_7__ {void* len; void* type; } ;
struct mwifiex_ie_types_ps_param {TYPE_3__ header; struct mwifiex_ps_param param; } ;
struct mwifiex_ie_types_header {int dummy; } ;
struct TYPE_8__ {void* len; void* type; } ;
struct mwifiex_ie_types_auto_ds_param {void* deep_sleep_timeout; TYPE_4__ header; } ;
struct mwifiex_ds_auto_ds {scalar_t__ idle_time; } ;
struct mwifiex_adapter {scalar_t__ null_pkt_interval; scalar_t__ multiple_dtim; scalar_t__ bcn_miss_time_out; scalar_t__ local_listen_interval; scalar_t__ adhoc_awake_period; scalar_t__ delay_to_ps; scalar_t__ enhanced_ps_mode; } ;
struct TYPE_6__ {void* ps_bitmap; } ;
struct host_cmd_ds_802_11_ps_mode_enh {TYPE_2__ params; void* action; } ;
struct TYPE_5__ {struct host_cmd_ds_802_11_ps_mode_enh psmode_enh; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 int BITMAP_AUTO_DS ; 
 int BITMAP_STA_PS ; 
 int /*<<< orphan*/  CMD ; 
 scalar_t__ DIS_AUTO_PS ; 
 scalar_t__ EN_AUTO_PS ; 
 scalar_t__ GET_PS ; 
 scalar_t__ HostCmd_CMD_802_11_PS_MODE_ENH ; 
 scalar_t__ S_DS_GEN ; 
 scalar_t__ TLV_TYPE_AUTO_DS_PARAM ; 
 scalar_t__ TLV_TYPE_PS_PARAM ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 

int mwifiex_cmd_enh_power_mode(struct mwifiex_private *priv,
			       struct host_cmd_ds_command *cmd,
			       u16 cmd_action, uint16_t ps_bitmap,
			       struct mwifiex_ds_auto_ds *auto_ds)
{
	struct host_cmd_ds_802_11_ps_mode_enh *psmode_enh =
		&cmd->params.psmode_enh;
	u8 *tlv;
	u16 cmd_size = 0;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_PS_MODE_ENH);
	if (cmd_action == DIS_AUTO_PS) {
		psmode_enh->action = cpu_to_le16(DIS_AUTO_PS);
		psmode_enh->params.ps_bitmap = cpu_to_le16(ps_bitmap);
		cmd->size = cpu_to_le16(S_DS_GEN + sizeof(psmode_enh->action) +
					sizeof(psmode_enh->params.ps_bitmap));
	} else if (cmd_action == GET_PS) {
		psmode_enh->action = cpu_to_le16(GET_PS);
		psmode_enh->params.ps_bitmap = cpu_to_le16(ps_bitmap);
		cmd->size = cpu_to_le16(S_DS_GEN + sizeof(psmode_enh->action) +
					sizeof(psmode_enh->params.ps_bitmap));
	} else if (cmd_action == EN_AUTO_PS) {
		psmode_enh->action = cpu_to_le16(EN_AUTO_PS);
		psmode_enh->params.ps_bitmap = cpu_to_le16(ps_bitmap);
		cmd_size = S_DS_GEN + sizeof(psmode_enh->action) +
					sizeof(psmode_enh->params.ps_bitmap);
		tlv = (u8 *) cmd + cmd_size;
		if (ps_bitmap & BITMAP_STA_PS) {
			struct mwifiex_adapter *adapter = priv->adapter;
			struct mwifiex_ie_types_ps_param *ps_tlv =
				(struct mwifiex_ie_types_ps_param *) tlv;
			struct mwifiex_ps_param *ps_mode = &ps_tlv->param;
			ps_tlv->header.type = cpu_to_le16(TLV_TYPE_PS_PARAM);
			ps_tlv->header.len = cpu_to_le16(sizeof(*ps_tlv) -
					sizeof(struct mwifiex_ie_types_header));
			cmd_size += sizeof(*ps_tlv);
			tlv += sizeof(*ps_tlv);
			mwifiex_dbg(priv->adapter, CMD,
				    "cmd: PS Command: Enter PS\n");
			ps_mode->null_pkt_interval =
					cpu_to_le16(adapter->null_pkt_interval);
			ps_mode->multiple_dtims =
					cpu_to_le16(adapter->multiple_dtim);
			ps_mode->bcn_miss_timeout =
					cpu_to_le16(adapter->bcn_miss_time_out);
			ps_mode->local_listen_interval =
				cpu_to_le16(adapter->local_listen_interval);
			ps_mode->adhoc_wake_period =
				cpu_to_le16(adapter->adhoc_awake_period);
			ps_mode->delay_to_ps =
					cpu_to_le16(adapter->delay_to_ps);
			ps_mode->mode = cpu_to_le16(adapter->enhanced_ps_mode);

		}
		if (ps_bitmap & BITMAP_AUTO_DS) {
			struct mwifiex_ie_types_auto_ds_param *auto_ds_tlv =
				(struct mwifiex_ie_types_auto_ds_param *) tlv;
			u16 idletime = 0;

			auto_ds_tlv->header.type =
				cpu_to_le16(TLV_TYPE_AUTO_DS_PARAM);
			auto_ds_tlv->header.len =
				cpu_to_le16(sizeof(*auto_ds_tlv) -
					sizeof(struct mwifiex_ie_types_header));
			cmd_size += sizeof(*auto_ds_tlv);
			tlv += sizeof(*auto_ds_tlv);
			if (auto_ds)
				idletime = auto_ds->idle_time;
			mwifiex_dbg(priv->adapter, CMD,
				    "cmd: PS Command: Enter Auto Deep Sleep\n");
			auto_ds_tlv->deep_sleep_timeout = cpu_to_le16(idletime);
		}
		cmd->size = cpu_to_le16(cmd_size);
	}
	return 0;
}