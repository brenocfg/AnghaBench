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
typedef  int /*<<< orphan*/  u32 ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CURRENTPID ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  mga_driver_fence_wait (struct drm_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mga_wait_fence(struct drm_device *dev, void *data, struct drm_file *
file_priv)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	u32 *fence = data;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	DRM_DEBUG("pid=%d\n", DRM_CURRENTPID);

	mga_driver_fence_wait(dev, fence);
	return 0;
}