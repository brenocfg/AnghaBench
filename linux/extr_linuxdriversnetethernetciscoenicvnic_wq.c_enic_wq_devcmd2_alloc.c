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
struct vnic_wq {int /*<<< orphan*/  ring; int /*<<< orphan*/  ctrl; struct vnic_dev* vdev; scalar_t__ index; } ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RES_TYPE_DEVCMD2 ; 
 int vnic_dev_alloc_desc_ring (struct vnic_dev*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vnic_dev_get_res (struct vnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_wq_disable (struct vnic_wq*) ; 

int enic_wq_devcmd2_alloc(struct vnic_dev *vdev, struct vnic_wq *wq,
			  unsigned int desc_count, unsigned int desc_size)
{
	int err;

	wq->index = 0;
	wq->vdev = vdev;

	wq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_DEVCMD2, 0);
	if (!wq->ctrl)
		return -EINVAL;
	vnic_wq_disable(wq);
	err = vnic_dev_alloc_desc_ring(vdev, &wq->ring, desc_count, desc_size);

	return err;
}