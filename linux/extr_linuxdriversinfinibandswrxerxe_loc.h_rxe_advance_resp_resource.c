#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ res_head; } ;
struct TYPE_3__ {scalar_t__ max_dest_rd_atomic; } ;
struct rxe_qp {TYPE_2__ resp; TYPE_1__ attr; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void rxe_advance_resp_resource(struct rxe_qp *qp)
{
	qp->resp.res_head++;
	if (unlikely(qp->resp.res_head == qp->attr.max_dest_rd_atomic))
		qp->resp.res_head = 0;
}