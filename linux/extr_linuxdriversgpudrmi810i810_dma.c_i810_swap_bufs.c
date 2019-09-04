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
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  i810_dma_dispatch_swap (struct drm_device*) ; 

__attribute__((used)) static int i810_swap_bufs(struct drm_device *dev, void *data,
			  struct drm_file *file_priv)
{
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	i810_dma_dispatch_swap(dev);
	return 0;
}