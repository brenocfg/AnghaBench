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
typedef  int u32 ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct iwl_fw_error_dump_data {scalar_t__ data; void* len; void* type; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  gen2; } ;

/* Variables and functions */
 int FH_MEM_LOWER_BOUND ; 
 int /*<<< orphan*/  FH_MEM_LOWER_BOUND_GEN2 ; 
 int FH_MEM_UPPER_BOUND ; 
 int /*<<< orphan*/  FH_MEM_UPPER_BOUND_GEN2 ; 
 int IWL_FW_ERROR_DUMP_FH_REGS ; 
 void* cpu_to_le32 (int) ; 
 struct iwl_fw_error_dump_data* iwl_fw_error_next_data (struct iwl_fw_error_dump_data*) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (struct iwl_trans*,unsigned long*) ; 
 int iwl_trans_pcie_read32 (struct iwl_trans*,int) ; 
 int iwl_trans_pcie_read_prph (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (struct iwl_trans*,unsigned long*) ; 
 int iwl_umac_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 iwl_trans_pcie_fh_regs_dump(struct iwl_trans *trans,
				       struct iwl_fw_error_dump_data **data)
{
	u32 fh_regs_len = FH_MEM_UPPER_BOUND - FH_MEM_LOWER_BOUND;
	unsigned long flags;
	__le32 *val;
	int i;

	if (!iwl_trans_grab_nic_access(trans, &flags))
		return 0;

	(*data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_FH_REGS);
	(*data)->len = cpu_to_le32(fh_regs_len);
	val = (void *)(*data)->data;

	if (!trans->trans_cfg->gen2)
		for (i = FH_MEM_LOWER_BOUND; i < FH_MEM_UPPER_BOUND;
		     i += sizeof(u32))
			*val++ = cpu_to_le32(iwl_trans_pcie_read32(trans, i));
	else
		for (i = iwl_umac_prph(trans, FH_MEM_LOWER_BOUND_GEN2);
		     i < iwl_umac_prph(trans, FH_MEM_UPPER_BOUND_GEN2);
		     i += sizeof(u32))
			*val++ = cpu_to_le32(iwl_trans_pcie_read_prph(trans,
								      i));

	iwl_trans_release_nic_access(trans, &flags);

	*data = iwl_fw_error_next_data(*data);

	return sizeof(**data) + fh_regs_len;
}