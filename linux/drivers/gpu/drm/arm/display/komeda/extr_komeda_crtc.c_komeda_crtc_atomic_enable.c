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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  komeda_crtc_do_flush (struct drm_crtc*,struct drm_crtc_state*) ; 
 int /*<<< orphan*/  komeda_crtc_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_kcrtc (struct drm_crtc*) ; 

__attribute__((used)) static void
komeda_crtc_atomic_enable(struct drm_crtc *crtc,
			  struct drm_crtc_state *old)
{
	komeda_crtc_prepare(to_kcrtc(crtc));
	drm_crtc_vblank_on(crtc);
	komeda_crtc_do_flush(crtc, old);
}