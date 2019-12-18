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
struct rcar_du_crtc {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 void drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  rcar_du_crtc_crc_cleanup (struct rcar_du_crtc*) ; 
 struct rcar_du_crtc* to_rcar_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void rcar_du_crtc_cleanup(struct drm_crtc *crtc)
{
	struct rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	rcar_du_crtc_crc_cleanup(rcrtc);

	return drm_crtc_cleanup(crtc);
}