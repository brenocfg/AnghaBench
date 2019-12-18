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
struct zx_vou_hw {int /*<<< orphan*/  dev; scalar_t__ timing; } ;
struct zx_crtc_regs {scalar_t__ timing_pi_shift; scalar_t__ timing_shift; scalar_t__ sec_vtiming; scalar_t__ fir_vtiming; scalar_t__ fir_htiming; scalar_t__ fir_active; } ;
struct zx_crtc_bits {int sec_vactive_shift; int sec_vactive_mask; int polarity_mask; int polarity_shift; int interlace_select; int pi_enable; int tc_enable; } ;
struct zx_crtc {int /*<<< orphan*/  pixclk; scalar_t__ chnreg; struct zx_crtc_bits* bits; struct zx_crtc_regs* regs; struct zx_vou_hw* vou; } ;
struct videomode {int vactive; int hactive; int flags; scalar_t__ vfront_porch; scalar_t__ vback_porch; scalar_t__ vsync_len; scalar_t__ hfront_porch; scalar_t__ hback_porch; scalar_t__ hsync_len; } ;
struct drm_display_mode {int flags; int clock; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* state; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int BACK_PORCH (scalar_t__) ; 
 scalar_t__ CHN_CTRL0 ; 
 scalar_t__ CHN_CTRL1 ; 
 int CHN_ENABLE ; 
 scalar_t__ CHN_INTERLACE_BUF_CTRL ; 
 int CHN_INTERLACE_EN ; 
 int CHN_SCREEN_H_MASK ; 
 int CHN_SCREEN_H_SHIFT ; 
 int CHN_SCREEN_W_MASK ; 
 int CHN_SCREEN_W_SHIFT ; 
 int DISPLAY_FLAGS_HSYNC_LOW ; 
 int DISPLAY_FLAGS_VSYNC_LOW ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int FRONT_PORCH (scalar_t__) ; 
 int H_ACTIVE (int) ; 
 int H_PI_SHIFT_VAL ; 
 int H_SHIFT_VAL ; 
 int POL_HSYNC_SHIFT ; 
 int POL_VSYNC_SHIFT ; 
 scalar_t__ SCAN_CTRL ; 
 scalar_t__ SEC_V_ACTIVE ; 
 int SYNC_WIDE (scalar_t__) ; 
 scalar_t__ TIMING_CTRL ; 
 scalar_t__ TIMING_TC_ENABLE ; 
 int V_ACTIVE (int) ; 
 int V_SHIFT_VAL ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_display_mode_to_videomode (struct drm_display_mode*,struct videomode*) ; 
 struct zx_crtc* to_zx_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  vou_chn_set_update (struct zx_crtc*) ; 
 int zx_readl (scalar_t__) ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,int) ; 
 int /*<<< orphan*/  zx_writel_mask (scalar_t__,int,int) ; 

__attribute__((used)) static void zx_crtc_atomic_enable(struct drm_crtc *crtc,
				  struct drm_crtc_state *old_state)
{
	struct drm_display_mode *mode = &crtc->state->adjusted_mode;
	bool interlaced = mode->flags & DRM_MODE_FLAG_INTERLACE;
	struct zx_crtc *zcrtc = to_zx_crtc(crtc);
	struct zx_vou_hw *vou = zcrtc->vou;
	const struct zx_crtc_regs *regs = zcrtc->regs;
	const struct zx_crtc_bits *bits = zcrtc->bits;
	struct videomode vm;
	u32 scan_mask;
	u32 pol = 0;
	u32 val;
	int ret;

	drm_display_mode_to_videomode(mode, &vm);

	/* Set up timing parameters */
	val = V_ACTIVE((interlaced ? vm.vactive / 2 : vm.vactive) - 1);
	val |= H_ACTIVE(vm.hactive - 1);
	zx_writel(vou->timing + regs->fir_active, val);

	val = SYNC_WIDE(vm.hsync_len - 1);
	val |= BACK_PORCH(vm.hback_porch - 1);
	val |= FRONT_PORCH(vm.hfront_porch - 1);
	zx_writel(vou->timing + regs->fir_htiming, val);

	val = SYNC_WIDE(vm.vsync_len - 1);
	val |= BACK_PORCH(vm.vback_porch - 1);
	val |= FRONT_PORCH(vm.vfront_porch - 1);
	zx_writel(vou->timing + regs->fir_vtiming, val);

	if (interlaced) {
		u32 shift = bits->sec_vactive_shift;
		u32 mask = bits->sec_vactive_mask;

		val = zx_readl(vou->timing + SEC_V_ACTIVE);
		val &= ~mask;
		val |= ((vm.vactive / 2 - 1) << shift) & mask;
		zx_writel(vou->timing + SEC_V_ACTIVE, val);

		val = SYNC_WIDE(vm.vsync_len - 1);
		/*
		 * The vback_porch for the second field needs to shift one on
		 * the value for the first field.
		 */
		val |= BACK_PORCH(vm.vback_porch);
		val |= FRONT_PORCH(vm.vfront_porch - 1);
		zx_writel(vou->timing + regs->sec_vtiming, val);
	}

	/* Set up polarities */
	if (vm.flags & DISPLAY_FLAGS_VSYNC_LOW)
		pol |= 1 << POL_VSYNC_SHIFT;
	if (vm.flags & DISPLAY_FLAGS_HSYNC_LOW)
		pol |= 1 << POL_HSYNC_SHIFT;

	zx_writel_mask(vou->timing + TIMING_CTRL, bits->polarity_mask,
		       pol << bits->polarity_shift);

	/* Setup SHIFT register by following what ZTE BSP does */
	val = H_SHIFT_VAL;
	if (interlaced)
		val |= V_SHIFT_VAL << 16;
	zx_writel(vou->timing + regs->timing_shift, val);
	zx_writel(vou->timing + regs->timing_pi_shift, H_PI_SHIFT_VAL);

	/* Progressive or interlace scan select */
	scan_mask = bits->interlace_select | bits->pi_enable;
	zx_writel_mask(vou->timing + SCAN_CTRL, scan_mask,
		       interlaced ? scan_mask : 0);

	/* Enable TIMING_CTRL */
	zx_writel_mask(vou->timing + TIMING_TC_ENABLE, bits->tc_enable,
		       bits->tc_enable);

	/* Configure channel screen size */
	zx_writel_mask(zcrtc->chnreg + CHN_CTRL1, CHN_SCREEN_W_MASK,
		       vm.hactive << CHN_SCREEN_W_SHIFT);
	zx_writel_mask(zcrtc->chnreg + CHN_CTRL1, CHN_SCREEN_H_MASK,
		       vm.vactive << CHN_SCREEN_H_SHIFT);

	/* Configure channel interlace buffer control */
	zx_writel_mask(zcrtc->chnreg + CHN_INTERLACE_BUF_CTRL, CHN_INTERLACE_EN,
		       interlaced ? CHN_INTERLACE_EN : 0);

	/* Update channel */
	vou_chn_set_update(zcrtc);

	/* Enable channel */
	zx_writel_mask(zcrtc->chnreg + CHN_CTRL0, CHN_ENABLE, CHN_ENABLE);

	drm_crtc_vblank_on(crtc);

	ret = clk_set_rate(zcrtc->pixclk, mode->clock * 1000);
	if (ret) {
		DRM_DEV_ERROR(vou->dev, "failed to set pixclk rate: %d\n", ret);
		return;
	}

	ret = clk_prepare_enable(zcrtc->pixclk);
	if (ret)
		DRM_DEV_ERROR(vou->dev, "failed to enable pixclk: %d\n", ret);
}