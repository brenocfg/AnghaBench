#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtproc_info {size_t num_bufs; size_t buf_size; int /*<<< orphan*/  bufs_dma; int /*<<< orphan*/  rbufs; int /*<<< orphan*/  vdev; int /*<<< orphan*/  endpoints; scalar_t__ ns_ept; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct virtio_device {TYPE_2__ dev; TYPE_1__* config; struct virtproc_info* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* del_vqs ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __rpmsg_destroy_ept (struct virtproc_info*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,int) ; 
 int device_for_each_child (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct virtproc_info*) ; 
 int /*<<< orphan*/  rpmsg_remove_device ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpmsg_remove(struct virtio_device *vdev)
{
	struct virtproc_info *vrp = vdev->priv;
	size_t total_buf_space = vrp->num_bufs * vrp->buf_size;
	int ret;

	vdev->config->reset(vdev);

	ret = device_for_each_child(&vdev->dev, NULL, rpmsg_remove_device);
	if (ret)
		dev_warn(&vdev->dev, "can't remove rpmsg device: %d\n", ret);

	if (vrp->ns_ept)
		__rpmsg_destroy_ept(vrp, vrp->ns_ept);

	idr_destroy(&vrp->endpoints);

	vdev->config->del_vqs(vrp->vdev);

	dma_free_coherent(vdev->dev.parent, total_buf_space,
			  vrp->rbufs, vrp->bufs_dma);

	kfree(vrp);
}