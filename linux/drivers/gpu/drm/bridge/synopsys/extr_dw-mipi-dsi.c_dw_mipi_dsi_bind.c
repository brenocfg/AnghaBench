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
struct dw_mipi_dsi {int /*<<< orphan*/  bridge; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int drm_bridge_attach (struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int dw_mipi_dsi_bind(struct dw_mipi_dsi *dsi, struct drm_encoder *encoder)
{
	int ret;

	ret = drm_bridge_attach(encoder, &dsi->bridge, NULL);
	if (ret) {
		DRM_ERROR("Failed to initialize bridge with drm\n");
		return ret;
	}

	return ret;
}