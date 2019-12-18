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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCCR_BCBLACK ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int GCR_LTDCEN ; 
 int IER_FUIE ; 
 int IER_RRIE ; 
 int IER_TERRIE ; 
 int /*<<< orphan*/  LTDC_BCCR ; 
 int /*<<< orphan*/  LTDC_GCR ; 
 int /*<<< orphan*/  LTDC_IER ; 
 int /*<<< orphan*/  LTDC_SRCR ; 
 int SRCR_VBR ; 
 struct ltdc_device* crtc_to_ltdc (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltdc_crtc_atomic_enable(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_state)
{
	struct ltdc_device *ldev = crtc_to_ltdc(crtc);

	DRM_DEBUG_DRIVER("\n");

	/* Sets the background color value */
	reg_write(ldev->regs, LTDC_BCCR, BCCR_BCBLACK);

	/* Enable IRQ */
	reg_set(ldev->regs, LTDC_IER, IER_RRIE | IER_FUIE | IER_TERRIE);

	/* Commit shadow registers = update planes at next vblank */
	reg_set(ldev->regs, LTDC_SRCR, SRCR_VBR);

	/* Enable LTDC */
	reg_set(ldev->regs, LTDC_GCR, GCR_LTDCEN);

	drm_crtc_vblank_on(crtc);
}