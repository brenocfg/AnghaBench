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
struct ltdc_device {int /*<<< orphan*/  regs; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int GCR_LTDCEN ; 
 int IER_FUIE ; 
 int IER_RRIE ; 
 int IER_TERRIE ; 
 int /*<<< orphan*/  LTDC_GCR ; 
 int /*<<< orphan*/  LTDC_IER ; 
 int /*<<< orphan*/  LTDC_SRCR ; 
 int /*<<< orphan*/  SRCR_IMR ; 
 struct ltdc_device* crtc_to_ltdc (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltdc_crtc_atomic_disable(struct drm_crtc *crtc,
				     struct drm_crtc_state *old_state)
{
	struct ltdc_device *ldev = crtc_to_ltdc(crtc);
	struct drm_device *ddev = crtc->dev;

	DRM_DEBUG_DRIVER("\n");

	drm_crtc_vblank_off(crtc);

	/* disable LTDC */
	reg_clear(ldev->regs, LTDC_GCR, GCR_LTDCEN);

	/* disable IRQ */
	reg_clear(ldev->regs, LTDC_IER, IER_RRIE | IER_FUIE | IER_TERRIE);

	/* immediately commit disable of layers before switching off LTDC */
	reg_set(ldev->regs, LTDC_SRCR, SRCR_IMR);

	pm_runtime_put_sync(ddev->dev);
}