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
typedef  int /*<<< orphan*/  u32 ;
struct omap_crtc {int /*<<< orphan*/  name; scalar_t__ ignore_digit_sync_lost; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_IRQ_SYNC_LOST_DIGIT ; 
 int /*<<< orphan*/  DRM_ERROR_RATELIMITED (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 

void omap_crtc_error_irq(struct drm_crtc *crtc, u32 irqstatus)
{
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);

	if (omap_crtc->ignore_digit_sync_lost) {
		irqstatus &= ~DISPC_IRQ_SYNC_LOST_DIGIT;
		if (!irqstatus)
			return;
	}

	DRM_ERROR_RATELIMITED("%s: errors: %08x\n", omap_crtc->name, irqstatus);
}