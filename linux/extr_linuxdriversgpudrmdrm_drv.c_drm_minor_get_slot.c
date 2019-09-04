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
struct drm_minor {int dummy; } ;
struct drm_device {struct drm_minor* render; struct drm_minor* primary; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DRM_MINOR_PRIMARY 129 
#define  DRM_MINOR_RENDER 128 

__attribute__((used)) static struct drm_minor **drm_minor_get_slot(struct drm_device *dev,
					     unsigned int type)
{
	switch (type) {
	case DRM_MINOR_PRIMARY:
		return &dev->primary;
	case DRM_MINOR_RENDER:
		return &dev->render;
	default:
		BUG();
	}
}