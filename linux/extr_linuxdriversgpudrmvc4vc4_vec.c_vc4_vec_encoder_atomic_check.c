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
struct vc4_vec_tv_mode {int /*<<< orphan*/  mode; } ;
struct drm_encoder {int dummy; } ;
struct drm_crtc_state {int /*<<< orphan*/  adjusted_mode; } ;
struct TYPE_2__ {size_t mode; } ;
struct drm_connector_state {scalar_t__ crtc; TYPE_1__ tv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  drm_mode_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vc4_vec_tv_mode* vc4_vec_tv_modes ; 

__attribute__((used)) static int vc4_vec_encoder_atomic_check(struct drm_encoder *encoder,
					struct drm_crtc_state *crtc_state,
					struct drm_connector_state *conn_state)
{
	const struct vc4_vec_tv_mode *vec_mode;

	vec_mode = &vc4_vec_tv_modes[conn_state->tv.mode];

	if (conn_state->crtc &&
	    !drm_mode_equal(vec_mode->mode, &crtc_state->adjusted_mode))
		return -EINVAL;

	return 0;
}