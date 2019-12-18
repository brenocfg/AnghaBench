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
struct drm_clip_rect {int x1; int x2; int y1; int y2; } ;
typedef  int /*<<< orphan*/  drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CCE_PACKET0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int R128_AUX1_SC_EN ; 
 int /*<<< orphan*/  R128_AUX1_SC_LEFT ; 
 int R128_AUX1_SC_MODE_OR ; 
 int R128_AUX2_SC_EN ; 
 int /*<<< orphan*/  R128_AUX2_SC_LEFT ; 
 int R128_AUX2_SC_MODE_OR ; 
 int R128_AUX3_SC_EN ; 
 int /*<<< orphan*/  R128_AUX3_SC_LEFT ; 
 int R128_AUX3_SC_MODE_OR ; 
 int /*<<< orphan*/  R128_AUX_SC_CNTL ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static void r128_emit_clip_rects(drm_r128_private_t *dev_priv,
				 struct drm_clip_rect *boxes, int count)
{
	u32 aux_sc_cntl = 0x00000000;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING((count < 3 ? count : 3) * 5 + 2);

	if (count >= 1) {
		OUT_RING(CCE_PACKET0(R128_AUX1_SC_LEFT, 3));
		OUT_RING(boxes[0].x1);
		OUT_RING(boxes[0].x2 - 1);
		OUT_RING(boxes[0].y1);
		OUT_RING(boxes[0].y2 - 1);

		aux_sc_cntl |= (R128_AUX1_SC_EN | R128_AUX1_SC_MODE_OR);
	}
	if (count >= 2) {
		OUT_RING(CCE_PACKET0(R128_AUX2_SC_LEFT, 3));
		OUT_RING(boxes[1].x1);
		OUT_RING(boxes[1].x2 - 1);
		OUT_RING(boxes[1].y1);
		OUT_RING(boxes[1].y2 - 1);

		aux_sc_cntl |= (R128_AUX2_SC_EN | R128_AUX2_SC_MODE_OR);
	}
	if (count >= 3) {
		OUT_RING(CCE_PACKET0(R128_AUX3_SC_LEFT, 3));
		OUT_RING(boxes[2].x1);
		OUT_RING(boxes[2].x2 - 1);
		OUT_RING(boxes[2].y1);
		OUT_RING(boxes[2].y2 - 1);

		aux_sc_cntl |= (R128_AUX3_SC_EN | R128_AUX3_SC_MODE_OR);
	}

	OUT_RING(CCE_PACKET0(R128_AUX_SC_CNTL, 0));
	OUT_RING(aux_sc_cntl);

	ADVANCE_RING();
}