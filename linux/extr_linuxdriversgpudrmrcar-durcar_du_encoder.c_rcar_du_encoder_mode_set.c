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
struct rcar_du_encoder {int /*<<< orphan*/  output; } ;
struct drm_encoder {int dummy; } ;
struct drm_crtc_state {int /*<<< orphan*/  crtc; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcar_du_crtc_route_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rcar_du_encoder* to_rcar_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void rcar_du_encoder_mode_set(struct drm_encoder *encoder,
				     struct drm_crtc_state *crtc_state,
				     struct drm_connector_state *conn_state)
{
	struct rcar_du_encoder *renc = to_rcar_encoder(encoder);

	rcar_du_crtc_route_output(crtc_state->crtc, renc->output);
}