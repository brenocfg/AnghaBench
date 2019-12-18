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
struct vnic_rq {unsigned int index; int /*<<< orphan*/  ring; int /*<<< orphan*/  ctrl; struct vnic_dev* vdev; } ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RES_TYPE_RQ ; 
 int /*<<< orphan*/  vdev_err (struct vnic_dev*,char*,unsigned int) ; 
 int vnic_dev_alloc_desc_ring (struct vnic_dev*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vnic_dev_get_res (struct vnic_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int vnic_rq_alloc_bufs (struct vnic_rq*) ; 
 int /*<<< orphan*/  vnic_rq_disable (struct vnic_rq*) ; 
 int /*<<< orphan*/  vnic_rq_free (struct vnic_rq*) ; 

int vnic_rq_alloc(struct vnic_dev *vdev, struct vnic_rq *rq, unsigned int index,
	unsigned int desc_count, unsigned int desc_size)
{
	int err;

	rq->index = index;
	rq->vdev = vdev;

	rq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_RQ, index);
	if (!rq->ctrl) {
		vdev_err(vdev, "Failed to hook RQ[%d] resource\n", index);
		return -EINVAL;
	}

	vnic_rq_disable(rq);

	err = vnic_dev_alloc_desc_ring(vdev, &rq->ring, desc_count, desc_size);
	if (err)
		return err;

	err = vnic_rq_alloc_bufs(rq);
	if (err) {
		vnic_rq_free(rq);
		return err;
	}

	return 0;
}