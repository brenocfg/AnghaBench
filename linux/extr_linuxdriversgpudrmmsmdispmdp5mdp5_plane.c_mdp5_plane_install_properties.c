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
struct msm_drm_private {struct drm_property** plane_property; } ;
struct drm_property {int dummy; } ;
struct drm_plane {int /*<<< orphan*/  base; struct drm_device* dev; } ;
struct drm_mode_object {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 size_t PLANE_PROP_ZPOS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,struct drm_property*,int) ; 
 struct drm_property* drm_property_create_range (struct drm_device*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mdp5_plane_install_rotation_property (struct drm_device*,struct drm_plane*) ; 

__attribute__((used)) static void mdp5_plane_install_properties(struct drm_plane *plane,
		struct drm_mode_object *obj)
{
	struct drm_device *dev = plane->dev;
	struct msm_drm_private *dev_priv = dev->dev_private;
	struct drm_property *prop;

#define INSTALL_PROPERTY(name, NAME, init_val, fnc, ...) do { \
		prop = dev_priv->plane_property[PLANE_PROP_##NAME]; \
		if (!prop) { \
			prop = drm_property_##fnc(dev, 0, #name, \
				##__VA_ARGS__); \
			if (!prop) { \
				dev_warn(dev->dev, \
					"Create property %s failed\n", \
					#name); \
				return; \
			} \
			dev_priv->plane_property[PLANE_PROP_##NAME] = prop; \
		} \
		drm_object_attach_property(&plane->base, prop, init_val); \
	} while (0)

#define INSTALL_RANGE_PROPERTY(name, NAME, min, max, init_val) \
		INSTALL_PROPERTY(name, NAME, init_val, \
				create_range, min, max)

#define INSTALL_ENUM_PROPERTY(name, NAME, init_val) \
		INSTALL_PROPERTY(name, NAME, init_val, \
				create_enum, name##_prop_enum_list, \
				ARRAY_SIZE(name##_prop_enum_list))

	INSTALL_RANGE_PROPERTY(zpos, ZPOS, 1, 255, 1);

	mdp5_plane_install_rotation_property(dev, plane);

#undef INSTALL_RANGE_PROPERTY
#undef INSTALL_ENUM_PROPERTY
#undef INSTALL_PROPERTY
}