#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vlv_fifo_state {int* plane; } ;
struct TYPE_8__ {struct vlv_fifo_state fifo_state; } ;
struct TYPE_9__ {TYPE_3__ vlv; } ;
struct TYPE_6__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  fifo_changed; TYPE_4__ wm; TYPE_1__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_2__ base; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_5__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSPARB ; 
 int /*<<< orphan*/  DSPARB2 ; 
 int /*<<< orphan*/  DSPARB3 ; 
 int I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
#define  PIPE_A 130 
#define  PIPE_B 129 
#define  PIPE_C 128 
 size_t PLANE_CURSOR ; 
 size_t PLANE_PRIMARY ; 
 size_t PLANE_SPRITE0 ; 
 size_t PLANE_SPRITE1 ; 
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRITEA ; 
 int /*<<< orphan*/  SPRITEA_HI ; 
 int /*<<< orphan*/  SPRITEB ; 
 int /*<<< orphan*/  SPRITEB_HI ; 
 int /*<<< orphan*/  SPRITEC ; 
 int /*<<< orphan*/  SPRITEC_HI ; 
 int /*<<< orphan*/  SPRITED ; 
 int /*<<< orphan*/  SPRITED_HI ; 
 int /*<<< orphan*/  SPRITEE ; 
 int /*<<< orphan*/  SPRITEE_HI ; 
 int /*<<< orphan*/  SPRITEF ; 
 int /*<<< orphan*/  SPRITEF_HI ; 
 int VLV_FIFO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_vlv_fifo_size (struct intel_crtc*,int,int,int) ; 

__attribute__((used)) static void vlv_atomic_update_fifo(struct intel_atomic_state *state,
				   struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	const struct vlv_fifo_state *fifo_state =
		&crtc_state->wm.vlv.fifo_state;
	int sprite0_start, sprite1_start, fifo_size;

	if (!crtc_state->fifo_changed)
		return;

	sprite0_start = fifo_state->plane[PLANE_PRIMARY];
	sprite1_start = fifo_state->plane[PLANE_SPRITE0] + sprite0_start;
	fifo_size = fifo_state->plane[PLANE_SPRITE1] + sprite1_start;

	WARN_ON(fifo_state->plane[PLANE_CURSOR] != 63);
	WARN_ON(fifo_size != 511);

	trace_vlv_fifo_size(crtc, sprite0_start, sprite1_start, fifo_size);

	/*
	 * uncore.lock serves a double purpose here. It allows us to
	 * use the less expensive I915_{READ,WRITE}_FW() functions, and
	 * it protects the DSPARB registers from getting clobbered by
	 * parallel updates from multiple pipes.
	 *
	 * intel_pipe_update_start() has already disabled interrupts
	 * for us, so a plain spin_lock() is sufficient here.
	 */
	spin_lock(&dev_priv->uncore.lock);

	switch (crtc->pipe) {
		uint32_t dsparb, dsparb2, dsparb3;
	case PIPE_A:
		dsparb = I915_READ_FW(DSPARB);
		dsparb2 = I915_READ_FW(DSPARB2);

		dsparb &= ~(VLV_FIFO(SPRITEA, 0xff) |
			    VLV_FIFO(SPRITEB, 0xff));
		dsparb |= (VLV_FIFO(SPRITEA, sprite0_start) |
			   VLV_FIFO(SPRITEB, sprite1_start));

		dsparb2 &= ~(VLV_FIFO(SPRITEA_HI, 0x1) |
			     VLV_FIFO(SPRITEB_HI, 0x1));
		dsparb2 |= (VLV_FIFO(SPRITEA_HI, sprite0_start >> 8) |
			   VLV_FIFO(SPRITEB_HI, sprite1_start >> 8));

		I915_WRITE_FW(DSPARB, dsparb);
		I915_WRITE_FW(DSPARB2, dsparb2);
		break;
	case PIPE_B:
		dsparb = I915_READ_FW(DSPARB);
		dsparb2 = I915_READ_FW(DSPARB2);

		dsparb &= ~(VLV_FIFO(SPRITEC, 0xff) |
			    VLV_FIFO(SPRITED, 0xff));
		dsparb |= (VLV_FIFO(SPRITEC, sprite0_start) |
			   VLV_FIFO(SPRITED, sprite1_start));

		dsparb2 &= ~(VLV_FIFO(SPRITEC_HI, 0xff) |
			     VLV_FIFO(SPRITED_HI, 0xff));
		dsparb2 |= (VLV_FIFO(SPRITEC_HI, sprite0_start >> 8) |
			   VLV_FIFO(SPRITED_HI, sprite1_start >> 8));

		I915_WRITE_FW(DSPARB, dsparb);
		I915_WRITE_FW(DSPARB2, dsparb2);
		break;
	case PIPE_C:
		dsparb3 = I915_READ_FW(DSPARB3);
		dsparb2 = I915_READ_FW(DSPARB2);

		dsparb3 &= ~(VLV_FIFO(SPRITEE, 0xff) |
			     VLV_FIFO(SPRITEF, 0xff));
		dsparb3 |= (VLV_FIFO(SPRITEE, sprite0_start) |
			    VLV_FIFO(SPRITEF, sprite1_start));

		dsparb2 &= ~(VLV_FIFO(SPRITEE_HI, 0xff) |
			     VLV_FIFO(SPRITEF_HI, 0xff));
		dsparb2 |= (VLV_FIFO(SPRITEE_HI, sprite0_start >> 8) |
			   VLV_FIFO(SPRITEF_HI, sprite1_start >> 8));

		I915_WRITE_FW(DSPARB3, dsparb3);
		I915_WRITE_FW(DSPARB2, dsparb2);
		break;
	default:
		break;
	}

	POSTING_READ_FW(DSPARB);

	spin_unlock(&dev_priv->uncore.lock);
}