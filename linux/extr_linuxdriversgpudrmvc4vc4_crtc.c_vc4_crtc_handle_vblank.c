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
struct vc4_crtc {int /*<<< orphan*/  base; int /*<<< orphan*/  t_vblank; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  vc4_crtc_handle_page_flip (struct vc4_crtc*) ; 

void vc4_crtc_handle_vblank(struct vc4_crtc *crtc)
{
	crtc->t_vblank = ktime_get();
	drm_crtc_handle_vblank(&crtc->base);
	vc4_crtc_handle_page_flip(crtc);
}