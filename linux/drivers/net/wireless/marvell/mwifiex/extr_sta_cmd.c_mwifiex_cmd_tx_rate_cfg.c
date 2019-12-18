#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct mwifiex_rate_scope {void** vht_mcs_rate_bitmap; void** ht_mcs_rate_bitmap; void* ofdm_rate_bitmap; void* hr_dsss_rate_bitmap; void* length; void* type; } ;
struct mwifiex_rate_drop_pattern {scalar_t__ rate_drop_mode; void* length; void* type; } ;
struct mwifiex_private {int* bitmap_rates; TYPE_2__* adapter; } ;
struct mwifiex_ie_types_header {int dummy; } ;
struct host_cmd_ds_tx_rate_cfg {scalar_t__ cfg_index; void* action; } ;
struct TYPE_3__ {struct host_cmd_ds_tx_rate_cfg tx_rate_cfg; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;
struct TYPE_4__ {scalar_t__ fw_api_ver; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 int HostCmd_CMD_TX_RATE_CFG ; 
 scalar_t__ MWIFIEX_FW_V15 ; 
 int S_DS_GEN ; 
 int TLV_TYPE_RATE_DROP_CONTROL ; 
 int TLV_TYPE_RATE_SCOPE ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static int mwifiex_cmd_tx_rate_cfg(struct mwifiex_private *priv,
				   struct host_cmd_ds_command *cmd,
				   u16 cmd_action, u16 *pbitmap_rates)
{
	struct host_cmd_ds_tx_rate_cfg *rate_cfg = &cmd->params.tx_rate_cfg;
	struct mwifiex_rate_scope *rate_scope;
	struct mwifiex_rate_drop_pattern *rate_drop;
	u32 i;

	cmd->command = cpu_to_le16(HostCmd_CMD_TX_RATE_CFG);

	rate_cfg->action = cpu_to_le16(cmd_action);
	rate_cfg->cfg_index = 0;

	rate_scope = (struct mwifiex_rate_scope *) ((u8 *) rate_cfg +
		      sizeof(struct host_cmd_ds_tx_rate_cfg));
	rate_scope->type = cpu_to_le16(TLV_TYPE_RATE_SCOPE);
	rate_scope->length = cpu_to_le16
		(sizeof(*rate_scope) - sizeof(struct mwifiex_ie_types_header));
	if (pbitmap_rates != NULL) {
		rate_scope->hr_dsss_rate_bitmap = cpu_to_le16(pbitmap_rates[0]);
		rate_scope->ofdm_rate_bitmap = cpu_to_le16(pbitmap_rates[1]);
		for (i = 0; i < ARRAY_SIZE(rate_scope->ht_mcs_rate_bitmap); i++)
			rate_scope->ht_mcs_rate_bitmap[i] =
				cpu_to_le16(pbitmap_rates[2 + i]);
		if (priv->adapter->fw_api_ver == MWIFIEX_FW_V15) {
			for (i = 0;
			     i < ARRAY_SIZE(rate_scope->vht_mcs_rate_bitmap);
			     i++)
				rate_scope->vht_mcs_rate_bitmap[i] =
					cpu_to_le16(pbitmap_rates[10 + i]);
		}
	} else {
		rate_scope->hr_dsss_rate_bitmap =
			cpu_to_le16(priv->bitmap_rates[0]);
		rate_scope->ofdm_rate_bitmap =
			cpu_to_le16(priv->bitmap_rates[1]);
		for (i = 0; i < ARRAY_SIZE(rate_scope->ht_mcs_rate_bitmap); i++)
			rate_scope->ht_mcs_rate_bitmap[i] =
				cpu_to_le16(priv->bitmap_rates[2 + i]);
		if (priv->adapter->fw_api_ver == MWIFIEX_FW_V15) {
			for (i = 0;
			     i < ARRAY_SIZE(rate_scope->vht_mcs_rate_bitmap);
			     i++)
				rate_scope->vht_mcs_rate_bitmap[i] =
					cpu_to_le16(priv->bitmap_rates[10 + i]);
		}
	}

	rate_drop = (struct mwifiex_rate_drop_pattern *) ((u8 *) rate_scope +
					     sizeof(struct mwifiex_rate_scope));
	rate_drop->type = cpu_to_le16(TLV_TYPE_RATE_DROP_CONTROL);
	rate_drop->length = cpu_to_le16(sizeof(rate_drop->rate_drop_mode));
	rate_drop->rate_drop_mode = 0;

	cmd->size =
		cpu_to_le16(S_DS_GEN + sizeof(struct host_cmd_ds_tx_rate_cfg) +
			    sizeof(struct mwifiex_rate_scope) +
			    sizeof(struct mwifiex_rate_drop_pattern));

	return 0;
}