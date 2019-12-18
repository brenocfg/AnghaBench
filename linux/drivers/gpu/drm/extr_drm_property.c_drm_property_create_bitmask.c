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
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_property {int dummy; } ;
struct drm_prop_enum_list {unsigned long long type; int /*<<< orphan*/  name; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_PROP_BITMASK ; 
 int drm_property_add_enum (struct drm_property*,unsigned long long,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create (struct drm_device*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  drm_property_destroy (struct drm_device*,struct drm_property*) ; 
 int hweight64 (unsigned long long) ; 

struct drm_property *drm_property_create_bitmask(struct drm_device *dev,
						 u32 flags, const char *name,
						 const struct drm_prop_enum_list *props,
						 int num_props,
						 uint64_t supported_bits)
{
	struct drm_property *property;
	int i, ret;
	int num_values = hweight64(supported_bits);

	flags |= DRM_MODE_PROP_BITMASK;

	property = drm_property_create(dev, flags, name, num_values);
	if (!property)
		return NULL;
	for (i = 0; i < num_props; i++) {
		if (!(supported_bits & (1ULL << props[i].type)))
			continue;

		ret = drm_property_add_enum(property,
					    props[i].type,
					    props[i].name);
		if (ret) {
			drm_property_destroy(dev, property);
			return NULL;
		}
	}

	return property;
}