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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  max_usec; } ;
struct vnic_dev {TYPE_1__ intr_coal_timer_info; } ;

/* Variables and functions */

u32 vnic_dev_get_intr_coal_timer_max(struct vnic_dev *vdev)
{
	return vdev->intr_coal_timer_info.max_usec;
}