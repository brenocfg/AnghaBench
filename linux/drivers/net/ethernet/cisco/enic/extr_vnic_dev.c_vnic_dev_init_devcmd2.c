#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct vnic_dev {int* args; int (* devcmd_rtn ) (struct vnic_dev*,int /*<<< orphan*/ ,int) ;TYPE_8__* devcmd2; } ;
struct TYPE_12__ {int /*<<< orphan*/  descs; } ;
struct TYPE_14__ {TYPE_2__* ctrl; TYPE_1__ ring; } ;
struct TYPE_15__ {scalar_t__ base_addr; int /*<<< orphan*/  descs; } ;
struct TYPE_16__ {int color; unsigned int posted; TYPE_3__ wq; TYPE_6__ results_ring; TYPE_2__* wq_ctrl; int /*<<< orphan*/  cmd_ring; int /*<<< orphan*/  result; void* result_size; } ;
struct TYPE_13__ {int /*<<< orphan*/  fetch_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INITIALIZE_DEVCMD2 ; 
 int /*<<< orphan*/  DEVCMD2_DESC_SIZE ; 
 void* DEVCMD2_RING_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VNIC_PADDR_TARGET ; 
 int _vnic_dev_cmd2 (struct vnic_dev*,int /*<<< orphan*/ ,int) ; 
 int enic_wq_devcmd2_alloc (struct vnic_dev*,TYPE_3__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enic_wq_init_start (TYPE_3__*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_8__*) ; 
 TYPE_8__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_err (struct vnic_dev*,char*) ; 
 int vnic_dev_alloc_desc_ring (struct vnic_dev*,TYPE_6__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_free_desc_ring (struct vnic_dev*,TYPE_6__*) ; 
 int /*<<< orphan*/  vnic_wq_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  vnic_wq_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  vnic_wq_free (TYPE_3__*) ; 

__attribute__((used)) static int vnic_dev_init_devcmd2(struct vnic_dev *vdev)
{
	int err;
	unsigned int fetch_index;

	if (vdev->devcmd2)
		return 0;

	vdev->devcmd2 = kzalloc(sizeof(*vdev->devcmd2), GFP_KERNEL);
	if (!vdev->devcmd2)
		return -ENOMEM;

	vdev->devcmd2->color = 1;
	vdev->devcmd2->result_size = DEVCMD2_RING_SIZE;
	err = enic_wq_devcmd2_alloc(vdev, &vdev->devcmd2->wq, DEVCMD2_RING_SIZE,
				    DEVCMD2_DESC_SIZE);
	if (err)
		goto err_free_devcmd2;

	fetch_index = ioread32(&vdev->devcmd2->wq.ctrl->fetch_index);
	if (fetch_index == 0xFFFFFFFF) { /* check for hardware gone  */
		vdev_err(vdev, "Fatal error in devcmd2 init - hardware surprise removal\n");
		err = -ENODEV;
		goto err_free_wq;
	}

	enic_wq_init_start(&vdev->devcmd2->wq, 0, fetch_index, fetch_index, 0,
			   0);
	vdev->devcmd2->posted = fetch_index;
	vnic_wq_enable(&vdev->devcmd2->wq);

	err = vnic_dev_alloc_desc_ring(vdev, &vdev->devcmd2->results_ring,
				       DEVCMD2_RING_SIZE, DEVCMD2_DESC_SIZE);
	if (err)
		goto err_disable_wq;

	vdev->devcmd2->result = vdev->devcmd2->results_ring.descs;
	vdev->devcmd2->cmd_ring = vdev->devcmd2->wq.ring.descs;
	vdev->devcmd2->wq_ctrl = vdev->devcmd2->wq.ctrl;
	vdev->args[0] = (u64)vdev->devcmd2->results_ring.base_addr |
			VNIC_PADDR_TARGET;
	vdev->args[1] = DEVCMD2_RING_SIZE;

	err = _vnic_dev_cmd2(vdev, CMD_INITIALIZE_DEVCMD2, 1000);
	if (err)
		goto err_free_desc_ring;

	vdev->devcmd_rtn = _vnic_dev_cmd2;

	return 0;

err_free_desc_ring:
	vnic_dev_free_desc_ring(vdev, &vdev->devcmd2->results_ring);
err_disable_wq:
	vnic_wq_disable(&vdev->devcmd2->wq);
err_free_wq:
	vnic_wq_free(&vdev->devcmd2->wq);
err_free_devcmd2:
	kfree(vdev->devcmd2);
	vdev->devcmd2 = NULL;

	return err;
}