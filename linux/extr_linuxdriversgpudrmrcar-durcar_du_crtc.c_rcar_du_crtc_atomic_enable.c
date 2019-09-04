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
struct rcar_du_crtc {int initialized; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcar_du_crtc_get (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_du_crtc_setup (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_du_crtc_start (struct rcar_du_crtc*) ; 
 struct rcar_du_crtc* to_rcar_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void rcar_du_crtc_atomic_enable(struct drm_crtc *crtc,
				       struct drm_crtc_state *old_state)
{
	struct rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	/*
	 * If the CRTC has already been setup by the .atomic_begin() handler we
	 * can skip the setup stage.
	 */
	if (!rcrtc->initialized) {
		rcar_du_crtc_get(rcrtc);
		rcar_du_crtc_setup(rcrtc);
		rcrtc->initialized = true;
	}

	rcar_du_crtc_start(rcrtc);
}