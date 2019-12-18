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
struct drm_crtc_state {scalar_t__ self_refresh_active; } ;
struct drm_connector_state {int self_refresh_aware; int /*<<< orphan*/  crtc; } ;
struct drm_connector {int dummy; } ;
struct drm_atomic_state {int dummy; } ;
struct analogix_dp_device {int /*<<< orphan*/  psr_supported; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 struct drm_connector_state* drm_atomic_get_new_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,int /*<<< orphan*/ ) ; 
 struct analogix_dp_device* to_dp (struct drm_connector*) ; 

__attribute__((used)) static int analogix_dp_atomic_check(struct drm_connector *connector,
				    struct drm_atomic_state *state)
{
	struct analogix_dp_device *dp = to_dp(connector);
	struct drm_connector_state *conn_state;
	struct drm_crtc_state *crtc_state;

	conn_state = drm_atomic_get_new_connector_state(state, connector);
	if (WARN_ON(!conn_state))
		return -ENODEV;

	conn_state->self_refresh_aware = true;

	if (!conn_state->crtc)
		return 0;

	crtc_state = drm_atomic_get_new_crtc_state(state, conn_state->crtc);
	if (!crtc_state)
		return 0;

	if (crtc_state->self_refresh_active && !dp->psr_supported)
		return -EINVAL;

	return 0;
}