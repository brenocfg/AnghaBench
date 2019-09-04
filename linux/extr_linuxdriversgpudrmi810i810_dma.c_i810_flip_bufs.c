#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_flipping; } ;
typedef  TYPE_1__ drm_i810_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  i810_dma_dispatch_flip (struct drm_device*) ; 
 int /*<<< orphan*/  i810_do_init_pageflip (struct drm_device*) ; 

__attribute__((used)) static int i810_flip_bufs(struct drm_device *dev, void *data,
			  struct drm_file *file_priv)
{
	drm_i810_private_t *dev_priv = dev->dev_private;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (!dev_priv->page_flipping)
		i810_do_init_pageflip(dev);

	i810_dma_dispatch_flip(dev);
	return 0;
}