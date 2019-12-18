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
struct intel_dp {TYPE_2__** mst_encoders; } ;
struct intel_crtc {size_t pipe; } ;
struct intel_connector {struct intel_dp* mst_port; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  crtc; } ;
struct drm_connector {int dummy; } ;
struct TYPE_3__ {struct drm_encoder base; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_encoder *intel_mst_atomic_best_encoder(struct drm_connector *connector,
							 struct drm_connector_state *state)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct intel_dp *intel_dp = intel_connector->mst_port;
	struct intel_crtc *crtc = to_intel_crtc(state->crtc);

	return &intel_dp->mst_encoders[crtc->pipe]->base.base;
}