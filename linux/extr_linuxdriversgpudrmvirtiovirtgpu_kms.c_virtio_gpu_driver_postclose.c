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
struct virtio_gpu_fpriv {int /*<<< orphan*/  ctx_id; } ;
struct virtio_gpu_device {int /*<<< orphan*/  has_virgl_3d; } ;
struct drm_file {struct virtio_gpu_fpriv* driver_priv; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct virtio_gpu_fpriv*) ; 
 int /*<<< orphan*/  virtio_gpu_context_destroy (struct virtio_gpu_device*,int /*<<< orphan*/ ) ; 

void virtio_gpu_driver_postclose(struct drm_device *dev, struct drm_file *file)
{
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct virtio_gpu_fpriv *vfpriv;

	if (!vgdev->has_virgl_3d)
		return;

	vfpriv = file->driver_priv;

	virtio_gpu_context_destroy(vgdev, vfpriv->ctx_id);
	kfree(vfpriv);
	file->driver_priv = NULL;
}