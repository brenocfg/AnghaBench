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
struct drm_dma {int granted_count; int request_count; int /*<<< orphan*/ * request_sizes; int /*<<< orphan*/ * request_indices; } ;
struct drm_device {int dummy; } ;
struct drm_buf {int /*<<< orphan*/  total; int /*<<< orphan*/  idx; struct drm_file* file_priv; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct drm_buf* r128_freelist_get (struct drm_device*) ; 

__attribute__((used)) static int r128_cce_get_buffers(struct drm_device *dev,
				struct drm_file *file_priv,
				struct drm_dma *d)
{
	int i;
	struct drm_buf *buf;

	for (i = d->granted_count; i < d->request_count; i++) {
		buf = r128_freelist_get(dev);
		if (!buf)
			return -EAGAIN;

		buf->file_priv = file_priv;

		if (copy_to_user(&d->request_indices[i], &buf->idx,
				     sizeof(buf->idx)))
			return -EFAULT;
		if (copy_to_user(&d->request_sizes[i], &buf->total,
				     sizeof(buf->total)))
			return -EFAULT;

		d->granted_count++;
	}
	return 0;
}