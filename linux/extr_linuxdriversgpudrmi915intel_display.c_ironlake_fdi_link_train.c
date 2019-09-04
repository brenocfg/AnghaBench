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
typedef  int u32 ;
struct intel_crtc_state {int /*<<< orphan*/  fdi_lanes; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int FDI_DP_PORT_WIDTH (int /*<<< orphan*/ ) ; 
 int FDI_DP_PORT_WIDTH_MASK ; 
 int FDI_LINK_TRAIN_NONE ; 
 int FDI_LINK_TRAIN_PATTERN_1 ; 
 int FDI_LINK_TRAIN_PATTERN_2 ; 
 int FDI_RX_BIT_LOCK ; 
 int /*<<< orphan*/  FDI_RX_CHICKEN (int) ; 
 int /*<<< orphan*/  FDI_RX_CTL (int) ; 
 int FDI_RX_ENABLE ; 
 int /*<<< orphan*/  FDI_RX_IIR (int) ; 
 int /*<<< orphan*/  FDI_RX_IMR (int) ; 
 int FDI_RX_PHASE_SYNC_POINTER_EN ; 
 int FDI_RX_PHASE_SYNC_POINTER_OVR ; 
 int FDI_RX_SYMBOL_LOCK ; 
 int /*<<< orphan*/  FDI_TX_CTL (int) ; 
 int FDI_TX_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_pipe_enabled (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ironlake_fdi_link_train(struct intel_crtc *crtc,
				    const struct intel_crtc_state *crtc_state)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	int pipe = crtc->pipe;
	i915_reg_t reg;
	u32 temp, tries;

	/* FDI needs bits from pipe first */
	assert_pipe_enabled(dev_priv, pipe);

	/* Train 1: umask FDI RX Interrupt symbol_lock and bit_lock bit
	   for train result */
	reg = FDI_RX_IMR(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_RX_SYMBOL_LOCK;
	temp &= ~FDI_RX_BIT_LOCK;
	I915_WRITE(reg, temp);
	I915_READ(reg);
	udelay(150);

	/* enable CPU FDI TX and PCH FDI RX */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_DP_PORT_WIDTH_MASK;
	temp |= FDI_DP_PORT_WIDTH(crtc_state->fdi_lanes);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	I915_WRITE(reg, temp | FDI_TX_ENABLE);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	I915_WRITE(reg, temp | FDI_RX_ENABLE);

	POSTING_READ(reg);
	udelay(150);

	/* Ironlake workaround, enable clock pointer after FDI enable*/
	I915_WRITE(FDI_RX_CHICKEN(pipe), FDI_RX_PHASE_SYNC_POINTER_OVR);
	I915_WRITE(FDI_RX_CHICKEN(pipe), FDI_RX_PHASE_SYNC_POINTER_OVR |
		   FDI_RX_PHASE_SYNC_POINTER_EN);

	reg = FDI_RX_IIR(pipe);
	for (tries = 0; tries < 5; tries++) {
		temp = I915_READ(reg);
		DRM_DEBUG_KMS("FDI_RX_IIR 0x%x\n", temp);

		if ((temp & FDI_RX_BIT_LOCK)) {
			DRM_DEBUG_KMS("FDI train 1 done.\n");
			I915_WRITE(reg, temp | FDI_RX_BIT_LOCK);
			break;
		}
	}
	if (tries == 5)
		DRM_ERROR("FDI train 1 fail!\n");

	/* Train 2 */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_2;
	I915_WRITE(reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_2;
	I915_WRITE(reg, temp);

	POSTING_READ(reg);
	udelay(150);

	reg = FDI_RX_IIR(pipe);
	for (tries = 0; tries < 5; tries++) {
		temp = I915_READ(reg);
		DRM_DEBUG_KMS("FDI_RX_IIR 0x%x\n", temp);

		if (temp & FDI_RX_SYMBOL_LOCK) {
			I915_WRITE(reg, temp | FDI_RX_SYMBOL_LOCK);
			DRM_DEBUG_KMS("FDI train 2 done.\n");
			break;
		}
	}
	if (tries == 5)
		DRM_ERROR("FDI train 2 fail!\n");

	DRM_DEBUG_KMS("FDI train done\n");

}