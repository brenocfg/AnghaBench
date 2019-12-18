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
typedef  size_t u8 ;
struct qlcnic_dcb_tc_cfg {int valid; size_t pgid; int /*<<< orphan*/  prio_type; TYPE_1__* prio_cfg; int /*<<< orphan*/  up_tc_map; } ;
struct qlcnic_dcb_param {int /*<<< orphan*/ * prio_pg_map; int /*<<< orphan*/ * hdr_prio_pfc_map; } ;
struct qlcnic_dcb_mbx_params {int /*<<< orphan*/  prio_tc_map; } ;
struct qlcnic_dcb_cee {TYPE_2__* pg_cfg; scalar_t__ pfc_mode_enable; struct qlcnic_dcb_tc_cfg* tc_cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  prio_count; } ;
struct TYPE_3__ {int valid; int /*<<< orphan*/  pfc_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_DCB_GET_MAP (size_t) ; 
 scalar_t__ QLC_DCB_GET_PFC_PRIO (int /*<<< orphan*/ ,size_t) ; 
 size_t QLC_DCB_GET_PGID_PRIO (int /*<<< orphan*/ ,size_t) ; 
 size_t QLC_DCB_GET_TC_PRIO (int /*<<< orphan*/ ,size_t) ; 
 size_t QLC_DCB_MAX_PRIO ; 
 int /*<<< orphan*/  QLC_PFC_FULL ; 
 int /*<<< orphan*/  QLC_PRIO_LINK ; 

__attribute__((used)) static void qlcnic_dcb_fill_cee_tc_params(struct qlcnic_dcb_mbx_params *mbx,
					  struct qlcnic_dcb_param *each,
					  struct qlcnic_dcb_cee *type)
{
	struct qlcnic_dcb_tc_cfg *tc_cfg;
	u8 i, tc, pgid;

	for (i = 0; i < QLC_DCB_MAX_PRIO; i++) {
		tc = QLC_DCB_GET_TC_PRIO(mbx->prio_tc_map, i);
		tc_cfg = &type->tc_cfg[tc];
		tc_cfg->valid = true;
		tc_cfg->up_tc_map |= QLC_DCB_GET_MAP(i);

		if (QLC_DCB_GET_PFC_PRIO(each->hdr_prio_pfc_map[1], i) &&
		    type->pfc_mode_enable) {
			tc_cfg->prio_cfg[i].valid = true;
			tc_cfg->prio_cfg[i].pfc_type = QLC_PFC_FULL;
		}

		if (i < 4)
			pgid = QLC_DCB_GET_PGID_PRIO(each->prio_pg_map[0], i);
		else
			pgid = QLC_DCB_GET_PGID_PRIO(each->prio_pg_map[1], i);

		tc_cfg->pgid = pgid;

		tc_cfg->prio_type = QLC_PRIO_LINK;
		type->pg_cfg[tc_cfg->pgid].prio_count++;
	}
}