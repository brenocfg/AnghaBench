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
struct rcar_du_crtc {int index; int /*<<< orphan*/  crtc; int /*<<< orphan*/  dev; int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPOR ; 
 int /*<<< orphan*/  BPOR_RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOOR ; 
 int /*<<< orphan*/  DOOR_RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS1PR ; 
 int /*<<< orphan*/  DS2PR ; 
 int /*<<< orphan*/  RCAR_DU_FEATURE_VSP1_SOURCE ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcar_du_crtc_set_display_timing (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_du_crtc_write (struct rcar_du_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_group_set_routing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_group_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rcar_du_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_vsp_enable (struct rcar_du_crtc*) ; 

__attribute__((used)) static void rcar_du_crtc_setup(struct rcar_du_crtc *rcrtc)
{
	/* Set display off and background to black */
	rcar_du_crtc_write(rcrtc, DOOR, DOOR_RGB(0, 0, 0));
	rcar_du_crtc_write(rcrtc, BPOR, BPOR_RGB(0, 0, 0));

	/* Configure display timings and output routing */
	rcar_du_crtc_set_display_timing(rcrtc);
	rcar_du_group_set_routing(rcrtc->group);

	/* Start with all planes disabled. */
	rcar_du_group_write(rcrtc->group, rcrtc->index % 2 ? DS2PR : DS1PR, 0);

	/* Enable the VSP compositor. */
	if (rcar_du_has(rcrtc->dev, RCAR_DU_FEATURE_VSP1_SOURCE))
		rcar_du_vsp_enable(rcrtc);

	/* Turn vertical blanking interrupt reporting on. */
	drm_crtc_vblank_on(&rcrtc->crtc);
}