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
typedef  size_t u8 ;
struct storm_defs {size_t block_id; } ;
struct qed_ptt {int dummy; } ;
struct dbg_tools_data {scalar_t__* block_in_reset; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;
struct fw_info {int dummy; } ;

/* Variables and functions */
 size_t MAX_DBG_STORMS ; 
 int /*<<< orphan*/  qed_read_storm_fw_info (struct qed_hwfn*,struct qed_ptt*,size_t,struct fw_info*) ; 
 struct storm_defs* s_storm_defs ; 

bool qed_read_fw_info(struct qed_hwfn *p_hwfn,
		      struct qed_ptt *p_ptt, struct fw_info *fw_info)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u8 storm_id;

	for (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) {
		struct storm_defs *storm = &s_storm_defs[storm_id];

		/* Skip Storm if it's in reset */
		if (dev_data->block_in_reset[storm->block_id])
			continue;

		/* Read FW info for the current Storm */
		qed_read_storm_fw_info(p_hwfn, p_ptt, storm_id, fw_info);

		return true;
	}

	return false;
}