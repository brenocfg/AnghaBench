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
struct drm_device {int dummy; } ;
struct drm_connector {int dummy; } ;
struct cirrus_connector {struct drm_connector base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cirrus_vga_connector_funcs ; 
 int /*<<< orphan*/  cirrus_vga_connector_helper_funcs ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 struct cirrus_connector* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_connector *cirrus_vga_init(struct drm_device *dev)
{
	struct drm_connector *connector;
	struct cirrus_connector *cirrus_connector;

	cirrus_connector = kzalloc(sizeof(struct cirrus_connector), GFP_KERNEL);
	if (!cirrus_connector)
		return NULL;

	connector = &cirrus_connector->base;

	drm_connector_init(dev, connector,
			   &cirrus_vga_connector_funcs, DRM_MODE_CONNECTOR_VGA);

	drm_connector_helper_add(connector, &cirrus_vga_connector_helper_funcs);

	drm_connector_register(connector);
	return connector;
}