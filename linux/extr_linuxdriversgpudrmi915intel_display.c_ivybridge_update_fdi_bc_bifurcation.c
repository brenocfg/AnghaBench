#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct drm_device* dev; } ;
struct intel_crtc {int pipe; TYPE_2__* config; TYPE_1__ base; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int fdi_lanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  PIPE_A 130 
#define  PIPE_B 129 
#define  PIPE_C 128 
 int /*<<< orphan*/  cpt_set_fdi_bc_bifurcation (struct drm_device*,int) ; 

__attribute__((used)) static void ivybridge_update_fdi_bc_bifurcation(struct intel_crtc *intel_crtc)
{
	struct drm_device *dev = intel_crtc->base.dev;

	switch (intel_crtc->pipe) {
	case PIPE_A:
		break;
	case PIPE_B:
		if (intel_crtc->config->fdi_lanes > 2)
			cpt_set_fdi_bc_bifurcation(dev, false);
		else
			cpt_set_fdi_bc_bifurcation(dev, true);

		break;
	case PIPE_C:
		cpt_set_fdi_bc_bifurcation(dev, true);

		break;
	default:
		BUG();
	}
}