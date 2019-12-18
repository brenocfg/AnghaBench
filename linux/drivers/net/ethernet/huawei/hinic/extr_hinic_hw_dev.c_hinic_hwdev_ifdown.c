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
struct hinic_cap {int /*<<< orphan*/  num_qps; } ;
struct hinic_func_to_io {int dummy; } ;
struct hinic_hwdev {struct hinic_cap nic_cap; struct hinic_func_to_io func_to_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_io_resources (struct hinic_hwdev*) ; 
 int /*<<< orphan*/  hinic_io_destroy_qps (struct hinic_func_to_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_io_free (struct hinic_func_to_io*) ; 

void hinic_hwdev_ifdown(struct hinic_hwdev *hwdev)
{
	struct hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	struct hinic_cap *nic_cap = &hwdev->nic_cap;

	clear_io_resources(hwdev);

	hinic_io_destroy_qps(func_to_io, nic_cap->num_qps);
	hinic_io_free(func_to_io);
}