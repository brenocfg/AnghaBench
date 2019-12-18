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
struct ntb_transport_qp {unsigned char qp_num; } ;

/* Variables and functions */

unsigned char ntb_transport_qp_num(struct ntb_transport_qp *qp)
{
	if (!qp)
		return 0;

	return qp->qp_num;
}