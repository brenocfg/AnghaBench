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
struct drm_connector {int dummy; } ;
struct mga_connector {int /*<<< orphan*/  i2c; struct drm_connector base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 struct mga_connector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mga_vga_connector_funcs ; 
 int /*<<< orphan*/  mga_vga_connector_helper_funcs ; 
 int /*<<< orphan*/  mgag200_i2c_create (struct drm_device*) ; 

__attribute__((used)) static struct drm_connector *mga_vga_init(struct drm_device *dev)
{
	struct drm_connector *connector;
	struct mga_connector *mga_connector;

	mga_connector = kzalloc(sizeof(struct mga_connector), GFP_KERNEL);
	if (!mga_connector)
		return NULL;

	connector = &mga_connector->base;

	drm_connector_init(dev, connector,
			   &mga_vga_connector_funcs, DRM_MODE_CONNECTOR_VGA);

	drm_connector_helper_add(connector, &mga_vga_connector_helper_funcs);

	drm_connector_register(connector);

	mga_connector->i2c = mgag200_i2c_create(dev);
	if (!mga_connector->i2c)
		DRM_ERROR("failed to add ddc bus\n");

	return connector;
}