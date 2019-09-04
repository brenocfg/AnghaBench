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
struct gma_crtc {struct gma_crtc* crtc_state; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  kfree (struct gma_crtc*) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 

void gma_crtc_destroy(struct drm_crtc *crtc)
{
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);

	kfree(gma_crtc->crtc_state);
	drm_crtc_cleanup(crtc);
	kfree(gma_crtc);
}