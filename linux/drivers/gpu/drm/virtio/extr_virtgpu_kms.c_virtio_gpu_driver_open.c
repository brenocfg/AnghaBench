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
struct virtio_gpu_fpriv {int ctx_id; } ;
struct virtio_gpu_device {int /*<<< orphan*/  has_virgl_3d; } ;
struct drm_file {struct virtio_gpu_fpriv* driver_priv; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_task_comm (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct virtio_gpu_fpriv*) ; 
 struct virtio_gpu_fpriv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int virtio_gpu_context_create (struct virtio_gpu_device*,int /*<<< orphan*/ ,char*) ; 

int virtio_gpu_driver_open(struct drm_device *dev, struct drm_file *file)
{
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct virtio_gpu_fpriv *vfpriv;
	int id;
	char dbgname[TASK_COMM_LEN];

	/* can't create contexts without 3d renderer */
	if (!vgdev->has_virgl_3d)
		return 0;

	/* allocate a virt GPU context for this opener */
	vfpriv = kzalloc(sizeof(*vfpriv), GFP_KERNEL);
	if (!vfpriv)
		return -ENOMEM;

	get_task_comm(dbgname, current);
	id = virtio_gpu_context_create(vgdev, strlen(dbgname), dbgname);
	if (id < 0) {
		kfree(vfpriv);
		return id;
	}

	vfpriv->ctx_id = id;
	file->driver_priv = vfpriv;
	return 0;
}