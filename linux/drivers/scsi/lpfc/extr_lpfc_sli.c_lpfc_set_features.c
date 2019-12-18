#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_sli4_cfg_mhdr {int dummy; } ;
struct lpfc_mbx_set_feature {int dummy; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_12__ {int feature; int param_len; } ;
struct TYPE_8__ {TYPE_7__ set_feature; } ;
struct TYPE_9__ {TYPE_1__ un; } ;
struct TYPE_10__ {TYPE_2__ mqe; } ;
struct TYPE_11__ {TYPE_3__ u; } ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_MBOX_OPCODE_SET_FEATURES ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_COMMON ; 
#define  LPFC_SET_MDS_DIAGS 129 
#define  LPFC_SET_UE_RECOVERY 128 
 int /*<<< orphan*/  LPFC_SLI4_MBX_EMBED ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 int /*<<< orphan*/  lpfc_mbx_set_feature_UER ; 
 int /*<<< orphan*/  lpfc_mbx_set_feature_mds ; 
 int /*<<< orphan*/  lpfc_mbx_set_feature_mds_deep_loopbk ; 
 int /*<<< orphan*/  lpfc_sli4_config (struct lpfc_hba*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_set_features(struct lpfc_hba *phba, LPFC_MBOXQ_t *mbox,
		  uint32_t feature)
{
	uint32_t len;

	len = sizeof(struct lpfc_mbx_set_feature) -
		sizeof(struct lpfc_sli4_cfg_mhdr);
	lpfc_sli4_config(phba, mbox, LPFC_MBOX_SUBSYSTEM_COMMON,
			 LPFC_MBOX_OPCODE_SET_FEATURES, len,
			 LPFC_SLI4_MBX_EMBED);

	switch (feature) {
	case LPFC_SET_UE_RECOVERY:
		bf_set(lpfc_mbx_set_feature_UER,
		       &mbox->u.mqe.un.set_feature, 1);
		mbox->u.mqe.un.set_feature.feature = LPFC_SET_UE_RECOVERY;
		mbox->u.mqe.un.set_feature.param_len = 8;
		break;
	case LPFC_SET_MDS_DIAGS:
		bf_set(lpfc_mbx_set_feature_mds,
		       &mbox->u.mqe.un.set_feature, 1);
		bf_set(lpfc_mbx_set_feature_mds_deep_loopbk,
		       &mbox->u.mqe.un.set_feature, 1);
		mbox->u.mqe.un.set_feature.feature = LPFC_SET_MDS_DIAGS;
		mbox->u.mqe.un.set_feature.param_len = 8;
		break;
	}

	return;
}