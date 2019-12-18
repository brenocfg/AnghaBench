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
struct vnic_wq {struct vnic_dev* vdev; scalar_t__ index; } ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_DEVCMD2 ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  svnic_wq_disable (struct vnic_wq*) ; 
 int vnic_wq_alloc_ring (struct vnic_dev*,struct vnic_wq*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int vnic_wq_get_ctrl (struct vnic_dev*,struct vnic_wq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vnic_wq_devcmd2_alloc(struct vnic_dev *vdev, struct vnic_wq *wq,
	unsigned int desc_count, unsigned int desc_size)
{
	int err;

	wq->index = 0;
	wq->vdev = vdev;

	err = vnic_wq_get_ctrl(vdev, wq, 0, RES_TYPE_DEVCMD2);
	if (err) {
		pr_err("Failed to get devcmd2 resource\n");

		return err;
	}

	svnic_wq_disable(wq);

	err = vnic_wq_alloc_ring(vdev, wq, 0, desc_count, desc_size);
	if (err)
		return err;

	return 0;
}