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
struct meson_cvbs_mode {int /*<<< orphan*/  mode; } ;
struct drm_encoder {int dummy; } ;
struct drm_crtc_state {int /*<<< orphan*/  mode; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MESON_CVBS_MODES_COUNT ; 
 scalar_t__ drm_mode_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct meson_cvbs_mode* meson_cvbs_modes ; 

__attribute__((used)) static int meson_venc_cvbs_encoder_atomic_check(struct drm_encoder *encoder,
					struct drm_crtc_state *crtc_state,
					struct drm_connector_state *conn_state)
{
	int i;

	for (i = 0; i < MESON_CVBS_MODES_COUNT; ++i) {
		struct meson_cvbs_mode *meson_mode = &meson_cvbs_modes[i];

		if (drm_mode_equal(&crtc_state->mode, &meson_mode->mode))
			return 0;
	}

	return -EINVAL;
}