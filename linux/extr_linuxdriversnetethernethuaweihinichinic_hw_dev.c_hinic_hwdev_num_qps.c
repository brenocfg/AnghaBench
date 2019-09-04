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
struct hinic_cap {int num_qps; } ;
struct hinic_hwdev {struct hinic_cap nic_cap; } ;

/* Variables and functions */

int hinic_hwdev_num_qps(struct hinic_hwdev *hwdev)
{
	struct hinic_cap *nic_cap = &hwdev->nic_cap;

	return nic_cap->num_qps;
}