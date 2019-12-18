#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {TYPE_4__* dest_tlv; TYPE_1__* fw_mon; scalar_t__ num_blocks; } ;
struct iwl_trans {TYPE_5__ dbg; TYPE_3__* trans_cfg; TYPE_2__* cfg; } ;
struct iwl_fw_error_dump_fw_mon {int dummy; } ;
struct iwl_fw_error_dump_data {int dummy; } ;
struct TYPE_9__ {int version; int base_shift; int end_shift; scalar_t__ monitor_mode; int /*<<< orphan*/  end_reg; int /*<<< orphan*/  base_reg; } ;
struct TYPE_8__ {scalar_t__ device_family; } ;
struct TYPE_7__ {scalar_t__ smem_offset; } ;
struct TYPE_6__ {int size; } ;

/* Variables and functions */
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int IWL_LDBG_M2S_BUF_BA_MSK ; 
 int IWL_LDBG_M2S_BUF_SIZE_MSK ; 
 int IWL_M2S_UNIT_SIZE ; 
 scalar_t__ MARBH_MODE ; 
 int iwl_read_prph (struct iwl_trans*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_trans_get_fw_monitor_len(struct iwl_trans *trans, u32 *len)
{
	if (trans->dbg.num_blocks) {
		*len += sizeof(struct iwl_fw_error_dump_data) +
			sizeof(struct iwl_fw_error_dump_fw_mon) +
			trans->dbg.fw_mon[0].size;
		return trans->dbg.fw_mon[0].size;
	} else if (trans->dbg.dest_tlv) {
		u32 base, end, cfg_reg, monitor_len;

		if (trans->dbg.dest_tlv->version == 1) {
			cfg_reg = le32_to_cpu(trans->dbg.dest_tlv->base_reg);
			cfg_reg = iwl_read_prph(trans, cfg_reg);
			base = (cfg_reg & IWL_LDBG_M2S_BUF_BA_MSK) <<
				trans->dbg.dest_tlv->base_shift;
			base *= IWL_M2S_UNIT_SIZE;
			base += trans->cfg->smem_offset;

			monitor_len =
				(cfg_reg & IWL_LDBG_M2S_BUF_SIZE_MSK) >>
				trans->dbg.dest_tlv->end_shift;
			monitor_len *= IWL_M2S_UNIT_SIZE;
		} else {
			base = le32_to_cpu(trans->dbg.dest_tlv->base_reg);
			end = le32_to_cpu(trans->dbg.dest_tlv->end_reg);

			base = iwl_read_prph(trans, base) <<
			       trans->dbg.dest_tlv->base_shift;
			end = iwl_read_prph(trans, end) <<
			      trans->dbg.dest_tlv->end_shift;

			/* Make "end" point to the actual end */
			if (trans->trans_cfg->device_family >=
			    IWL_DEVICE_FAMILY_8000 ||
			    trans->dbg.dest_tlv->monitor_mode == MARBH_MODE)
				end += (1 << trans->dbg.dest_tlv->end_shift);
			monitor_len = end - base;
		}
		*len += sizeof(struct iwl_fw_error_dump_data) +
			sizeof(struct iwl_fw_error_dump_fw_mon) +
			monitor_len;
		return monitor_len;
	}
	return 0;
}