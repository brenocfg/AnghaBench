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
struct vnic_wq {int /*<<< orphan*/  ctrl; } ;
struct vnic_dev {int dummy; } ;
typedef  enum vnic_res_type { ____Placeholder_vnic_res_type } vnic_res_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  vnic_dev_get_res (struct vnic_dev*,int,unsigned int) ; 

int vnic_wq_get_ctrl(struct vnic_dev *vdev, struct vnic_wq *wq,
		unsigned int index, enum vnic_res_type res_type)
{
	wq->ctrl = vnic_dev_get_res(vdev, res_type, index);

	if (!wq->ctrl)
		return -EINVAL;

	return 0;
}