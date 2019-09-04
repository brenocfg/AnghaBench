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
struct hinic_sq {int dummy; } ;
struct hinic_qp {struct hinic_sq sq; } ;
struct hinic_func_to_io {struct hinic_qp* qps; } ;
struct hinic_hwdev {struct hinic_func_to_io func_to_io; } ;

/* Variables and functions */
 int hinic_hwdev_num_qps (struct hinic_hwdev*) ; 

struct hinic_sq *hinic_hwdev_get_sq(struct hinic_hwdev *hwdev, int i)
{
	struct hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	struct hinic_qp *qp = &func_to_io->qps[i];

	if (i >= hinic_hwdev_num_qps(hwdev))
		return NULL;

	return &qp->sq;
}