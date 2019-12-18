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
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  IER_LIE ; 
 int /*<<< orphan*/  LTDC_IER ; 
 struct ltdc_device* crtc_to_ltdc (struct drm_crtc*) ; 
 int /*<<< orphan*/  reg_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltdc_crtc_disable_vblank(struct drm_crtc *crtc)
{
	struct ltdc_device *ldev = crtc_to_ltdc(crtc);

	DRM_DEBUG_DRIVER("\n");
	reg_clear(ldev->regs, LTDC_IER, IER_LIE);
}