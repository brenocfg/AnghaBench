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
struct vnic_dev {TYPE_1__* res; } ;
typedef  enum vnic_res_type { ____Placeholder_vnic_res_type } vnic_res_type ;
struct TYPE_2__ {unsigned int count; } ;

/* Variables and functions */

unsigned int vnic_dev_get_res_count(struct vnic_dev *vdev,
	enum vnic_res_type type)
{
	return vdev->res[type].count;
}