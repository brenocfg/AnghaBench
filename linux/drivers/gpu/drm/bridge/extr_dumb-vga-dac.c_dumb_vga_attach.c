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
struct dumb_vga {int /*<<< orphan*/  connector; int /*<<< orphan*/  ddc; } ;
struct drm_bridge {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int ENODEV ; 
 struct dumb_vga* drm_bridge_to_dumb_vga (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_connector_init_with_ddc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumb_vga_con_funcs ; 
 int /*<<< orphan*/  dumb_vga_con_helper_funcs ; 

__attribute__((used)) static int dumb_vga_attach(struct drm_bridge *bridge)
{
	struct dumb_vga *vga = drm_bridge_to_dumb_vga(bridge);
	int ret;

	if (!bridge->encoder) {
		DRM_ERROR("Missing encoder\n");
		return -ENODEV;
	}

	drm_connector_helper_add(&vga->connector,
				 &dumb_vga_con_helper_funcs);
	ret = drm_connector_init_with_ddc(bridge->dev, &vga->connector,
					  &dumb_vga_con_funcs,
					  DRM_MODE_CONNECTOR_VGA,
					  vga->ddc);
	if (ret) {
		DRM_ERROR("Failed to initialize connector\n");
		return ret;
	}

	drm_connector_attach_encoder(&vga->connector,
					  bridge->encoder);

	return 0;
}