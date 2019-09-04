#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rcar_du_device {int /*<<< orphan*/  dpad0_source; } ;
struct rcar_du_crtc {int /*<<< orphan*/  index; int /*<<< orphan*/  outputs; TYPE_1__* group; } ;
struct drm_crtc {int dummy; } ;
typedef  enum rcar_du_output { ____Placeholder_rcar_du_output } rcar_du_output ;
struct TYPE_2__ {struct rcar_du_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int RCAR_DU_OUTPUT_DPAD0 ; 
 struct rcar_du_crtc* to_rcar_crtc (struct drm_crtc*) ; 

void rcar_du_crtc_route_output(struct drm_crtc *crtc,
			       enum rcar_du_output output)
{
	struct rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	struct rcar_du_device *rcdu = rcrtc->group->dev;

	/*
	 * Store the route from the CRTC output to the DU output. The DU will be
	 * configured when starting the CRTC.
	 */
	rcrtc->outputs |= BIT(output);

	/*
	 * Store RGB routing to DPAD0, the hardware will be configured when
	 * starting the CRTC.
	 */
	if (output == RCAR_DU_OUTPUT_DPAD0)
		rcdu->dpad0_source = rcrtc->index;
}