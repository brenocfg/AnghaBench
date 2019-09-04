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
struct fsl_dcu_drm_device {int /*<<< orphan*/  pix_clk; int /*<<< orphan*/  regmap; } ;
struct drm_device {struct fsl_dcu_drm_device* dev_private; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCU_DCU_MODE ; 
 int /*<<< orphan*/  DCU_MODE_DCU_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCU_MODE_DCU_MODE_MASK ; 
 int /*<<< orphan*/  DCU_MODE_OFF ; 
 int /*<<< orphan*/  DCU_UPDATE_MODE ; 
 int /*<<< orphan*/  DCU_UPDATE_MODE_READREG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_helper_disable_planes_on_crtc (struct drm_crtc_state*,int) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_dcu_drm_crtc_atomic_disable(struct drm_crtc *crtc,
					struct drm_crtc_state *old_crtc_state)
{
	struct drm_device *dev = crtc->dev;
	struct fsl_dcu_drm_device *fsl_dev = dev->dev_private;

	/* always disable planes on the CRTC */
	drm_atomic_helper_disable_planes_on_crtc(old_crtc_state, true);

	drm_crtc_vblank_off(crtc);

	regmap_update_bits(fsl_dev->regmap, DCU_DCU_MODE,
			   DCU_MODE_DCU_MODE_MASK,
			   DCU_MODE_DCU_MODE(DCU_MODE_OFF));
	regmap_write(fsl_dev->regmap, DCU_UPDATE_MODE,
		     DCU_UPDATE_MODE_READREG);
	clk_disable_unprepare(fsl_dev->pix_clk);
}