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
typedef  int u32 ;
struct drm_property {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int DRM_MODE_PROP_SIGNED_RANGE ; 
 int /*<<< orphan*/  I642U64 (int /*<<< orphan*/ ) ; 
 struct drm_property* property_create_range (struct drm_device*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct drm_property *drm_property_create_signed_range(struct drm_device *dev,
						      u32 flags, const char *name,
						      int64_t min, int64_t max)
{
	return property_create_range(dev, DRM_MODE_PROP_SIGNED_RANGE | flags,
			name, I642U64(min), I642U64(max));
}