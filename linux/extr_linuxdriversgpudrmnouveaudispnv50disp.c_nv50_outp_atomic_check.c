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
struct nouveau_connector {int /*<<< orphan*/  native_mode; } ;
struct drm_encoder {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  connector; } ;

/* Variables and functions */
 struct nouveau_connector* nouveau_connector (int /*<<< orphan*/ ) ; 
 int nv50_outp_atomic_check_view (struct drm_encoder*,struct drm_crtc_state*,struct drm_connector_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_outp_atomic_check(struct drm_encoder *encoder,
		       struct drm_crtc_state *crtc_state,
		       struct drm_connector_state *conn_state)
{
	struct nouveau_connector *nv_connector =
		nouveau_connector(conn_state->connector);
	return nv50_outp_atomic_check_view(encoder, crtc_state, conn_state,
					   nv_connector->native_mode);
}