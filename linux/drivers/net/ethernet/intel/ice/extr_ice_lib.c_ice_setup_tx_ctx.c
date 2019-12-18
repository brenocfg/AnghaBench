#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {int type; int /*<<< orphan*/  idx; scalar_t__ vf_id; TYPE_2__* port_info; TYPE_1__* back; } ;
struct ice_tlan_ctx {int base; void* legacy_int; int /*<<< orphan*/  tso_qnum; void* tso_ena; int /*<<< orphan*/  src_vsi; int /*<<< orphan*/  vmvf_type; scalar_t__ vmvf_num; int /*<<< orphan*/  pf_num; int /*<<< orphan*/  qlen; int /*<<< orphan*/  port_num; } ;
struct ice_ring {int dma; int /*<<< orphan*/  count; struct ice_vsi* vsi; } ;
struct TYPE_6__ {scalar_t__ vf_base_id; } ;
struct ice_hw {TYPE_3__ func_caps; int /*<<< orphan*/  pf_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  lport; } ;
struct TYPE_4__ {struct ice_hw hw; } ;

/* Variables and functions */
 int ICE_TLAN_CTX_BASE_S ; 
 int /*<<< orphan*/  ICE_TLAN_CTX_VMVF_TYPE_PF ; 
 int /*<<< orphan*/  ICE_TLAN_CTX_VMVF_TYPE_VF ; 
 void* ICE_TX_LEGACY ; 
#define  ICE_VSI_LB 130 
#define  ICE_VSI_PF 129 
#define  ICE_VSI_VF 128 
 int /*<<< orphan*/  ice_get_hw_vsi_num (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_set_cgd_num (struct ice_tlan_ctx*,struct ice_ring*) ; 

__attribute__((used)) static void
ice_setup_tx_ctx(struct ice_ring *ring, struct ice_tlan_ctx *tlan_ctx, u16 pf_q)
{
	struct ice_vsi *vsi = ring->vsi;
	struct ice_hw *hw = &vsi->back->hw;

	tlan_ctx->base = ring->dma >> ICE_TLAN_CTX_BASE_S;

	tlan_ctx->port_num = vsi->port_info->lport;

	/* Transmit Queue Length */
	tlan_ctx->qlen = ring->count;

	ice_set_cgd_num(tlan_ctx, ring);

	/* PF number */
	tlan_ctx->pf_num = hw->pf_id;

	/* queue belongs to a specific VSI type
	 * VF / VM index should be programmed per vmvf_type setting:
	 * for vmvf_type = VF, it is VF number between 0-256
	 * for vmvf_type = VM, it is VM number between 0-767
	 * for PF or EMP this field should be set to zero
	 */
	switch (vsi->type) {
	case ICE_VSI_LB:
		/* fall through */
	case ICE_VSI_PF:
		tlan_ctx->vmvf_type = ICE_TLAN_CTX_VMVF_TYPE_PF;
		break;
	case ICE_VSI_VF:
		/* Firmware expects vmvf_num to be absolute VF ID */
		tlan_ctx->vmvf_num = hw->func_caps.vf_base_id + vsi->vf_id;
		tlan_ctx->vmvf_type = ICE_TLAN_CTX_VMVF_TYPE_VF;
		break;
	default:
		return;
	}

	/* make sure the context is associated with the right VSI */
	tlan_ctx->src_vsi = ice_get_hw_vsi_num(hw, vsi->idx);

	tlan_ctx->tso_ena = ICE_TX_LEGACY;
	tlan_ctx->tso_qnum = pf_q;

	/* Legacy or Advanced Host Interface:
	 * 0: Advanced Host Interface
	 * 1: Legacy Host Interface
	 */
	tlan_ctx->legacy_int = ICE_TX_LEGACY;
}