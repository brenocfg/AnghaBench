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
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int clock; } ;
struct drm_crtc_state {TYPE_1__ adjusted_mode; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int nv50_outp_atomic_check (struct drm_encoder*,struct drm_crtc_state*,struct drm_connector_state*) ; 

__attribute__((used)) static int
nv50_pior_atomic_check(struct drm_encoder *encoder,
		       struct drm_crtc_state *crtc_state,
		       struct drm_connector_state *conn_state)
{
	int ret = nv50_outp_atomic_check(encoder, crtc_state, conn_state);
	if (ret)
		return ret;
	crtc_state->adjusted_mode.clock *= 2;
	return 0;
}