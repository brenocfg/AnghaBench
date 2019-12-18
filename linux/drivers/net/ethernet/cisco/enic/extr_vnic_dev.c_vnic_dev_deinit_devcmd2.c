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
struct vnic_dev {TYPE_1__* devcmd2; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; int /*<<< orphan*/  results_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  vnic_dev_free_desc_ring (struct vnic_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_wq_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_wq_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vnic_dev_deinit_devcmd2(struct vnic_dev *vdev)
{
	vnic_dev_free_desc_ring(vdev, &vdev->devcmd2->results_ring);
	vnic_wq_disable(&vdev->devcmd2->wq);
	vnic_wq_free(&vdev->devcmd2->wq);
	kfree(vdev->devcmd2);
}