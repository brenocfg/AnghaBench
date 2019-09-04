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
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  intel_crt_set_dpms (struct intel_encoder*,struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_enable_crt(struct intel_encoder *encoder,
			     const struct intel_crtc_state *crtc_state,
			     const struct drm_connector_state *conn_state)
{
	intel_crt_set_dpms(encoder, crtc_state, DRM_MODE_DPMS_ON);
}