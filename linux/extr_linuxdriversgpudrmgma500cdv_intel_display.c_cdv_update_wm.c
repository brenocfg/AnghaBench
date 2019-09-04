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
struct gma_crtc {int pipe; } ;
struct drm_psb_private {TYPE_1__* ops; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_sr ) (struct drm_device*) ;} ;

/* Variables and functions */
 int CURSOR_A_FIFO_WM_MASK ; 
 int CURSOR_A_FIFO_WM_SHIFT ; 
 int CURSOR_B_FIFO_WM1_SHIFT ; 
 int CURSOR_B_FIFO_WM_MASK ; 
 int CURSOR_B_FIFO_WM_SHIFT ; 
 int CURSOR_FIFO_SR_WM1_SHIFT ; 
 int /*<<< orphan*/  DSPFW1 ; 
 int /*<<< orphan*/  DSPFW2 ; 
 int /*<<< orphan*/  DSPFW3 ; 
 int /*<<< orphan*/  DSPFW4 ; 
 int /*<<< orphan*/  DSPFW5 ; 
 int /*<<< orphan*/  DSPFW6 ; 
 int DSP_FIFO_SR_WM_MASK ; 
 int DSP_FIFO_SR_WM_SHIFT ; 
 int DSP_PLANE_A_FIFO_WM1_SHIFT ; 
 int DSP_PLANE_B_FIFO_WM1_SHIFT ; 
 int DSP_PLANE_C_FIFO_WM_MASK ; 
 int DSP_PLANE_C_FIFO_WM_SHIFT ; 
 int /*<<< orphan*/  FW_BLC_SELF ; 
 int FW_BLC_SELF_EN ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int cdv_intel_pipe_enabled (struct drm_device*,int) ; 
 scalar_t__ gma_pipe_has_type (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_wait_for_vblank (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 

void cdv_update_wm(struct drm_device *dev, struct drm_crtc *crtc)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);

	/* Is only one pipe enabled? */
	if (cdv_intel_pipe_enabled(dev, 0) ^ cdv_intel_pipe_enabled(dev, 1)) {
		u32 fw;

		fw = REG_READ(DSPFW1);
		fw &= ~DSP_FIFO_SR_WM_MASK;
		fw |= (0x7e << DSP_FIFO_SR_WM_SHIFT);
		fw &= ~CURSOR_B_FIFO_WM_MASK;
		fw |= (0x4 << CURSOR_B_FIFO_WM_SHIFT);
		REG_WRITE(DSPFW1, fw);

		fw = REG_READ(DSPFW2);
		fw &= ~CURSOR_A_FIFO_WM_MASK;
		fw |= (0x6 << CURSOR_A_FIFO_WM_SHIFT);
		fw &= ~DSP_PLANE_C_FIFO_WM_MASK;
		fw |= (0x8 << DSP_PLANE_C_FIFO_WM_SHIFT);
		REG_WRITE(DSPFW2, fw);

		REG_WRITE(DSPFW3, 0x36000000);

		/* ignore FW4 */

		/* Is pipe b lvds ? */
		if (gma_crtc->pipe == 1 &&
		    gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS)) {
			REG_WRITE(DSPFW5, 0x00040330);
		} else {
			fw = (3 << DSP_PLANE_B_FIFO_WM1_SHIFT) |
			     (4 << DSP_PLANE_A_FIFO_WM1_SHIFT) |
			     (3 << CURSOR_B_FIFO_WM1_SHIFT) |
			     (4 << CURSOR_FIFO_SR_WM1_SHIFT);
			REG_WRITE(DSPFW5, fw);
		}

		REG_WRITE(DSPFW6, 0x10);

		gma_wait_for_vblank(dev);

		/* enable self-refresh for single pipe active */
		REG_WRITE(FW_BLC_SELF, FW_BLC_SELF_EN);
		REG_READ(FW_BLC_SELF);
		gma_wait_for_vblank(dev);

	} else {

		/* HW team suggested values... */
		REG_WRITE(DSPFW1, 0x3f880808);
		REG_WRITE(DSPFW2, 0x0b020202);
		REG_WRITE(DSPFW3, 0x24000000);
		REG_WRITE(DSPFW4, 0x08030202);
		REG_WRITE(DSPFW5, 0x01010101);
		REG_WRITE(DSPFW6, 0x1d0);

		gma_wait_for_vblank(dev);

		dev_priv->ops->disable_sr(dev);
	}
}