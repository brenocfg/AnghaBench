#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dequeue_work; } ;
struct TYPE_6__ {int /*<<< orphan*/  dequeue_work; } ;
struct virtio_gpu_device {int vqs_ready; struct virtio_gpu_device* capsets; TYPE_4__* vdev; int /*<<< orphan*/  config_changed_work; TYPE_2__ cursorq; TYPE_1__ ctrlq; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;
struct TYPE_9__ {TYPE_3__* config; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* del_vqs ) (TYPE_4__*) ;int /*<<< orphan*/  (* reset ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct virtio_gpu_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  virtio_gpu_cleanup_cap_cache (struct virtio_gpu_device*) ; 
 int /*<<< orphan*/  virtio_gpu_free_vbufs (struct virtio_gpu_device*) ; 
 int /*<<< orphan*/  virtio_gpu_modeset_fini (struct virtio_gpu_device*) ; 
 int /*<<< orphan*/  virtio_gpu_ttm_fini (struct virtio_gpu_device*) ; 

void virtio_gpu_deinit(struct drm_device *dev)
{
	struct virtio_gpu_device *vgdev = dev->dev_private;

	vgdev->vqs_ready = false;
	flush_work(&vgdev->ctrlq.dequeue_work);
	flush_work(&vgdev->cursorq.dequeue_work);
	flush_work(&vgdev->config_changed_work);
	vgdev->vdev->config->reset(vgdev->vdev);
	vgdev->vdev->config->del_vqs(vgdev->vdev);

	virtio_gpu_modeset_fini(vgdev);
	virtio_gpu_ttm_fini(vgdev);
	virtio_gpu_free_vbufs(vgdev);
	virtio_gpu_cleanup_cap_cache(vgdev);
	kfree(vgdev->capsets);
	kfree(vgdev);
}