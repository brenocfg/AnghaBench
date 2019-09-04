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
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {int type; int /*<<< orphan*/  vsi_num; TYPE_2__* port_info; TYPE_1__* back; } ;
struct ice_tlan_ctx {int base; void* legacy_int; int /*<<< orphan*/  tso_qnum; void* tso_ena; int /*<<< orphan*/  src_vsi; int /*<<< orphan*/  vmvf_type; int /*<<< orphan*/  pf_num; int /*<<< orphan*/  qlen; int /*<<< orphan*/  port_num; } ;
struct ice_ring {int dma; int /*<<< orphan*/  count; struct ice_vsi* vsi; } ;
struct ice_hw {int /*<<< orphan*/  pf_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  lport; } ;
struct TYPE_3__ {struct ice_hw hw; } ;

/* Variables and functions */
 int ICE_TLAN_CTX_BASE_S ; 
 int /*<<< orphan*/  ICE_TLAN_CTX_VMVF_TYPE_PF ; 
 void* ICE_TX_LEGACY ; 
#define  ICE_VSI_PF 128 

__attribute__((used)) static void
ice_setup_tx_ctx(struct ice_ring *ring, struct ice_tlan_ctx *tlan_ctx, u16 pf_q)
{
	struct ice_vsi *vsi = ring->vsi;
	struct ice_hw *hw = &vsi->back->hw;

	tlan_ctx->base = ring->dma >> ICE_TLAN_CTX_BASE_S;

	tlan_ctx->port_num = vsi->port_info->lport;

	/* Transmit Queue Length */
	tlan_ctx->qlen = ring->count;

	/* PF number */
	tlan_ctx->pf_num = hw->pf_id;

	/* queue belongs to a specific VSI type
	 * VF / VM index should be programmed per vmvf_type setting:
	 * for vmvf_type = VF, it is VF number between 0-256
	 * for vmvf_type = VM, it is VM number between 0-767
	 * for PF or EMP this field should be set to zero
	 */
	switch (vsi->type) {
	case ICE_VSI_PF:
		tlan_ctx->vmvf_type = ICE_TLAN_CTX_VMVF_TYPE_PF;
		break;
	default:
		return;
	}

	/* make sure the context is associated with the right VSI */
	tlan_ctx->src_vsi = vsi->vsi_num;

	tlan_ctx->tso_ena = ICE_TX_LEGACY;
	tlan_ctx->tso_qnum = pf_q;

	/* Legacy or Advanced Host Interface:
	 * 0: Advanced Host Interface
	 * 1: Legacy Host Interface
	 */
	tlan_ctx->legacy_int = ICE_TX_LEGACY;
}