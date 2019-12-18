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
typedef  int u32 ;
struct iwl_trans {int dummy; } ;
struct iwl_fw_error_dump_fw_mon {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MON_DMARB_RD_CTL_ADDR ; 
 int /*<<< orphan*/  MON_DMARB_RD_DATA_ADDR ; 
 int iwl_read_umac_prph_no_grab (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (struct iwl_trans*,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (struct iwl_trans*,unsigned long*) ; 
 int /*<<< orphan*/  iwl_write_umac_prph_no_grab (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32
iwl_trans_pci_dump_marbh_monitor(struct iwl_trans *trans,
				 struct iwl_fw_error_dump_fw_mon *fw_mon_data,
				 u32 monitor_len)
{
	u32 buf_size_in_dwords = (monitor_len >> 2);
	u32 *buffer = (u32 *)fw_mon_data->data;
	unsigned long flags;
	u32 i;

	if (!iwl_trans_grab_nic_access(trans, &flags))
		return 0;

	iwl_write_umac_prph_no_grab(trans, MON_DMARB_RD_CTL_ADDR, 0x1);
	for (i = 0; i < buf_size_in_dwords; i++)
		buffer[i] = iwl_read_umac_prph_no_grab(trans,
						       MON_DMARB_RD_DATA_ADDR);
	iwl_write_umac_prph_no_grab(trans, MON_DMARB_RD_CTL_ADDR, 0x0);

	iwl_trans_release_nic_access(trans, &flags);

	return monitor_len;
}