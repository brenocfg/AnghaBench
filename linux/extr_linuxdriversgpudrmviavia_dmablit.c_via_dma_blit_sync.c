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
struct drm_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ engine; int /*<<< orphan*/  sync_handle; } ;
typedef  TYPE_1__ drm_via_blitsync_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int EINVAL ; 
 scalar_t__ VIA_NUM_BLIT_ENGINES ; 
 int via_dmablit_sync (struct drm_device*,int /*<<< orphan*/ ,scalar_t__) ; 

int
via_dma_blit_sync(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_via_blitsync_t *sync = data;
	int err;

	if (sync->engine >= VIA_NUM_BLIT_ENGINES)
		return -EINVAL;

	err = via_dmablit_sync(dev, sync->sync_handle, sync->engine);

	if (-EINTR == err)
		err = -EAGAIN;

	return err;
}