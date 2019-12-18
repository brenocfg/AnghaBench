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
typedef  size_t u8 ;
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct dbg_tools_data {scalar_t__ platform_id; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum dbg_storms { ____Placeholder_dbg_storms } dbg_storms ;
struct TYPE_2__ {int /*<<< orphan*/  has_vfc; } ;

/* Variables and functions */
 size_t DBG_PSTORM_ID ; 
 size_t MAX_DBG_STORMS ; 
 size_t NUM_VFC_RAM_TYPES ; 
 scalar_t__ PLATFORM_ASIC ; 
 int qed_grc_dump_vfc_cam (struct qed_hwfn*,struct qed_ptt*,int*,int,size_t) ; 
 int qed_grc_dump_vfc_ram (struct qed_hwfn*,struct qed_ptt*,int*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_grc_is_storm_included (struct qed_hwfn*,int) ; 
 TYPE_1__* s_storm_defs ; 
 int /*<<< orphan*/ * s_vfc_ram_defs ; 

__attribute__((used)) static u32 qed_grc_dump_vfc(struct qed_hwfn *p_hwfn,
			    struct qed_ptt *p_ptt, u32 *dump_buf, bool dump)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u8 storm_id, i;
	u32 offset = 0;

	for (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) {
		if (!qed_grc_is_storm_included(p_hwfn,
					       (enum dbg_storms)storm_id) ||
		    !s_storm_defs[storm_id].has_vfc ||
		    (storm_id == DBG_PSTORM_ID && dev_data->platform_id !=
		     PLATFORM_ASIC))
			continue;

		/* Read CAM */
		offset += qed_grc_dump_vfc_cam(p_hwfn,
					       p_ptt,
					       dump_buf + offset,
					       dump, storm_id);

		/* Read RAM */
		for (i = 0; i < NUM_VFC_RAM_TYPES; i++)
			offset += qed_grc_dump_vfc_ram(p_hwfn,
						       p_ptt,
						       dump_buf + offset,
						       dump,
						       storm_id,
						       &s_vfc_ram_defs[i]);
	}

	return offset;
}