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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qed_hwfn {int dummy; } ;
struct TYPE_2__ {int* prio; void* enabled; void* max_tc; void* willing; } ;
struct qed_dcbx_params {TYPE_1__ pfc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCBX_PFC_CAPS ; 
 int /*<<< orphan*/  DCBX_PFC_ENABLED ; 
 int /*<<< orphan*/  DCBX_PFC_PRI_EN_BITMAP ; 
 int DCBX_PFC_PRI_EN_BITMAP_PRI_0 ; 
 int DCBX_PFC_PRI_EN_BITMAP_PRI_1 ; 
 int DCBX_PFC_PRI_EN_BITMAP_PRI_2 ; 
 int DCBX_PFC_PRI_EN_BITMAP_PRI_3 ; 
 int DCBX_PFC_PRI_EN_BITMAP_PRI_4 ; 
 int DCBX_PFC_PRI_EN_BITMAP_PRI_5 ; 
 int DCBX_PFC_PRI_EN_BITMAP_PRI_6 ; 
 int DCBX_PFC_PRI_EN_BITMAP_PRI_7 ; 
 int /*<<< orphan*/  DCBX_PFC_WILLING ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,void*,int,void*,void*) ; 
 void* QED_MFW_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MSG_DCB ; 

__attribute__((used)) static void
qed_dcbx_get_pfc_data(struct qed_hwfn *p_hwfn,
		      u32 pfc, struct qed_dcbx_params *p_params)
{
	u8 pfc_map;

	p_params->pfc.willing = QED_MFW_GET_FIELD(pfc, DCBX_PFC_WILLING);
	p_params->pfc.max_tc = QED_MFW_GET_FIELD(pfc, DCBX_PFC_CAPS);
	p_params->pfc.enabled = QED_MFW_GET_FIELD(pfc, DCBX_PFC_ENABLED);
	pfc_map = QED_MFW_GET_FIELD(pfc, DCBX_PFC_PRI_EN_BITMAP);
	p_params->pfc.prio[0] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_0);
	p_params->pfc.prio[1] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_1);
	p_params->pfc.prio[2] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_2);
	p_params->pfc.prio[3] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_3);
	p_params->pfc.prio[4] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_4);
	p_params->pfc.prio[5] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_5);
	p_params->pfc.prio[6] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_6);
	p_params->pfc.prio[7] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_7);

	DP_VERBOSE(p_hwfn, QED_MSG_DCB,
		   "PFC params: willing %d, pfc_bitmap %u max_tc = %u enabled = %d\n",
		   p_params->pfc.willing, pfc_map, p_params->pfc.max_tc,
		   p_params->pfc.enabled);
}