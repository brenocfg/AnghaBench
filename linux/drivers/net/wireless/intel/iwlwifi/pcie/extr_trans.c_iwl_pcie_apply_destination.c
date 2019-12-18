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
typedef  int u32 ;
struct TYPE_8__ {int n_dest_reg; TYPE_3__* fw_mon; int /*<<< orphan*/  num_blocks; struct iwl_fw_dbg_dest_tlv_v1* dest_tlv; } ;
struct iwl_trans {TYPE_4__ dbg; TYPE_2__* trans_cfg; } ;
struct iwl_fw_dbg_dest_tlv_v1 {scalar_t__ monitor_mode; int base_shift; int end_shift; int /*<<< orphan*/  end_reg; int /*<<< orphan*/  base_reg; TYPE_1__* reg_ops; int /*<<< orphan*/  size_power; } ;
struct TYPE_7__ {int physical; int size; } ;
struct TYPE_6__ {scalar_t__ device_family; } ;
struct TYPE_5__ {int op; int /*<<< orphan*/  val; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int BIT (int) ; 
#define  CSR_ASSIGN 134 
#define  CSR_CLEARBIT 133 
#define  CSR_SETBIT 132 
 scalar_t__ EXTERNAL_MODE ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_trans*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int,...) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  MON_BUFF_BASE_ADDR_VER2 ; 
 int /*<<< orphan*/  MON_BUFF_END_ADDR_VER2 ; 
 int MON_BUFF_SHIFT_VER2 ; 
#define  PRPH_ASSIGN 131 
#define  PRPH_BLOCKBIT 130 
#define  PRPH_CLEARBIT 129 
#define  PRPH_SETBIT 128 
 int /*<<< orphan*/  get_fw_dbg_mode_string (scalar_t__) ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_clear_bits_prph (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_pcie_alloc_fw_monitor (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_read_prph (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_set_bits_prph (struct iwl_trans*,int,int) ; 
 scalar_t__ iwl_trans_dbg_ini_valid (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_write_umac_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

void iwl_pcie_apply_destination(struct iwl_trans *trans)
{
	const struct iwl_fw_dbg_dest_tlv_v1 *dest = trans->dbg.dest_tlv;
	int i;

	if (iwl_trans_dbg_ini_valid(trans)) {
		if (!trans->dbg.num_blocks)
			return;

		IWL_DEBUG_FW(trans,
			     "WRT: Applying DRAM buffer[0] destination\n");
		iwl_write_umac_prph(trans, MON_BUFF_BASE_ADDR_VER2,
				    trans->dbg.fw_mon[0].physical >>
				    MON_BUFF_SHIFT_VER2);
		iwl_write_umac_prph(trans, MON_BUFF_END_ADDR_VER2,
				    (trans->dbg.fw_mon[0].physical +
				     trans->dbg.fw_mon[0].size - 256) >>
				    MON_BUFF_SHIFT_VER2);
		return;
	}

	IWL_INFO(trans, "Applying debug destination %s\n",
		 get_fw_dbg_mode_string(dest->monitor_mode));

	if (dest->monitor_mode == EXTERNAL_MODE)
		iwl_pcie_alloc_fw_monitor(trans, dest->size_power);
	else
		IWL_WARN(trans, "PCI should have external buffer debug\n");

	for (i = 0; i < trans->dbg.n_dest_reg; i++) {
		u32 addr = le32_to_cpu(dest->reg_ops[i].addr);
		u32 val = le32_to_cpu(dest->reg_ops[i].val);

		switch (dest->reg_ops[i].op) {
		case CSR_ASSIGN:
			iwl_write32(trans, addr, val);
			break;
		case CSR_SETBIT:
			iwl_set_bit(trans, addr, BIT(val));
			break;
		case CSR_CLEARBIT:
			iwl_clear_bit(trans, addr, BIT(val));
			break;
		case PRPH_ASSIGN:
			iwl_write_prph(trans, addr, val);
			break;
		case PRPH_SETBIT:
			iwl_set_bits_prph(trans, addr, BIT(val));
			break;
		case PRPH_CLEARBIT:
			iwl_clear_bits_prph(trans, addr, BIT(val));
			break;
		case PRPH_BLOCKBIT:
			if (iwl_read_prph(trans, addr) & BIT(val)) {
				IWL_ERR(trans,
					"BIT(%u) in address 0x%x is 1, stopping FW configuration\n",
					val, addr);
				goto monitor;
			}
			break;
		default:
			IWL_ERR(trans, "FW debug - unknown OP %d\n",
				dest->reg_ops[i].op);
			break;
		}
	}

monitor:
	if (dest->monitor_mode == EXTERNAL_MODE && trans->dbg.fw_mon[0].size) {
		iwl_write_prph(trans, le32_to_cpu(dest->base_reg),
			       trans->dbg.fw_mon[0].physical >>
			       dest->base_shift);
		if (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_8000)
			iwl_write_prph(trans, le32_to_cpu(dest->end_reg),
				       (trans->dbg.fw_mon[0].physical +
					trans->dbg.fw_mon[0].size - 256) >>
						dest->end_shift);
		else
			iwl_write_prph(trans, le32_to_cpu(dest->end_reg),
				       (trans->dbg.fw_mon[0].physical +
					trans->dbg.fw_mon[0].size) >>
						dest->end_shift);
	}
}