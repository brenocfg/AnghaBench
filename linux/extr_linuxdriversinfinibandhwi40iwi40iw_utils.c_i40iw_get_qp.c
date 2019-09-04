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
struct ib_qp {int dummy; } ;
struct ib_device {int dummy; } ;
struct i40iw_device {int max_qp; TYPE_1__** qp_table; } ;
struct TYPE_2__ {struct ib_qp ibqp; } ;

/* Variables and functions */
 int IW_FIRST_QPN ; 
 struct i40iw_device* to_iwdev (struct ib_device*) ; 

struct ib_qp *i40iw_get_qp(struct ib_device *device, int qpn)
{
	struct i40iw_device *iwdev = to_iwdev(device);

	if ((qpn < IW_FIRST_QPN) || (qpn >= iwdev->max_qp))
		return NULL;

	return &iwdev->qp_table[qpn]->ibqp;
}