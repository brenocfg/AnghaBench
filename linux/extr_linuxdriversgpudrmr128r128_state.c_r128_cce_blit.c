#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device_dma {scalar_t__ buf_count; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; struct drm_device_dma* dma; } ;
typedef  int /*<<< orphan*/  drm_r128_private_t ;
struct TYPE_3__ {scalar_t__ idx; } ;
typedef  TYPE_1__ drm_r128_blit_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  DEV_INIT_TEST_WITH_RETURN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_CURRENTPID ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  RING_SPACE_TEST_WITH_RETURN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VB_AGE_TEST_WITH_RETURN (int /*<<< orphan*/ *) ; 
 int r128_cce_dispatch_blit (struct drm_device*,struct drm_file*,TYPE_1__*) ; 

__attribute__((used)) static int r128_cce_blit(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	struct drm_device_dma *dma = dev->dma;
	drm_r128_private_t *dev_priv = dev->dev_private;
	drm_r128_blit_t *blit = data;
	int ret;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	DRM_DEBUG("pid=%d index=%d\n", DRM_CURRENTPID, blit->idx);

	if (blit->idx < 0 || blit->idx >= dma->buf_count) {
		DRM_ERROR("buffer index %d (of %d max)\n",
			  blit->idx, dma->buf_count - 1);
		return -EINVAL;
	}

	RING_SPACE_TEST_WITH_RETURN(dev_priv);
	VB_AGE_TEST_WITH_RETURN(dev_priv);

	ret = r128_cce_dispatch_blit(dev, file_priv, blit);

	COMMIT_RING();
	return ret;
}