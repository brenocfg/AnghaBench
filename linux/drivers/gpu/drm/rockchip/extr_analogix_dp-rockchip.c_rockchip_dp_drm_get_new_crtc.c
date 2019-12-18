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
struct drm_encoder {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct drm_connector_state {struct drm_crtc* crtc; } ;
struct drm_connector {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 struct drm_connector* drm_atomic_get_new_connector_for_encoder (struct drm_atomic_state*,struct drm_encoder*) ; 
 struct drm_connector_state* drm_atomic_get_new_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 

__attribute__((used)) static
struct drm_crtc *rockchip_dp_drm_get_new_crtc(struct drm_encoder *encoder,
					      struct drm_atomic_state *state)
{
	struct drm_connector *connector;
	struct drm_connector_state *conn_state;

	connector = drm_atomic_get_new_connector_for_encoder(state, encoder);
	if (!connector)
		return NULL;

	conn_state = drm_atomic_get_new_connector_state(state, connector);
	if (!conn_state)
		return NULL;

	return conn_state->crtc;
}