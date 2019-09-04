#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  plane_3d_mask_c; int /*<<< orphan*/  sten_ref_mask_c; int /*<<< orphan*/  dp_write_mask; } ;
struct TYPE_5__ {TYPE_3__ context_state; } ;
typedef  TYPE_1__ drm_r128_sarea_t ;
struct TYPE_6__ {TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_r128_private_t ;
typedef  TYPE_3__ drm_r128_context_regs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  CCE_PACKET0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R128_DP_WRITE_MASK ; 
 int /*<<< orphan*/  R128_STEN_REF_MASK_C ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static __inline__ void r128_emit_masks(drm_r128_private_t *dev_priv)
{
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_r128_context_regs_t *ctx = &sarea_priv->context_state;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(5);

	OUT_RING(CCE_PACKET0(R128_DP_WRITE_MASK, 0));
	OUT_RING(ctx->dp_write_mask);

	OUT_RING(CCE_PACKET0(R128_STEN_REF_MASK_C, 1));
	OUT_RING(ctx->sten_ref_mask_c);
	OUT_RING(ctx->plane_3d_mask_c);

	ADVANCE_RING();
}