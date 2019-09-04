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
typedef  int u32 ;
struct TYPE_2__ {int div; int mul; } ;
struct vnic_dev {TYPE_1__ intr_coal_timer_info; } ;

/* Variables and functions */

u32 vnic_dev_intr_coal_timer_hw_to_usec(struct vnic_dev *vdev, u32 hw_cycles)
{
	return (hw_cycles * vdev->intr_coal_timer_info.div) /
		vdev->intr_coal_timer_info.mul;
}