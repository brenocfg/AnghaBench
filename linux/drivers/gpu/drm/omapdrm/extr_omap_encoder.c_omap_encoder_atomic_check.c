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
struct omap_encoder {int /*<<< orphan*/  output; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct drm_crtc_state {int /*<<< orphan*/  adjusted_mode; int /*<<< orphan*/  mode; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int MODE_OK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int omap_connector_mode_fixup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct omap_encoder* to_omap_encoder (struct drm_encoder*) ; 

__attribute__((used)) static int omap_encoder_atomic_check(struct drm_encoder *encoder,
				     struct drm_crtc_state *crtc_state,
				     struct drm_connector_state *conn_state)
{
	struct omap_encoder *omap_encoder = to_omap_encoder(encoder);
	enum drm_mode_status status;

	status = omap_connector_mode_fixup(omap_encoder->output,
					   &crtc_state->mode,
					   &crtc_state->adjusted_mode);
	if (status != MODE_OK) {
		dev_err(encoder->dev->dev, "invalid timings: %d\n", status);
		return -EINVAL;
	}

	return 0;
}