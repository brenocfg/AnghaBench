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
struct rxe_qp {int dummy; } ;
struct TYPE_4__ {struct rxe_qp* mr; } ;
struct TYPE_3__ {int /*<<< orphan*/  skb; } ;
struct resp_res {scalar_t__ type; TYPE_2__ read; TYPE_1__ atomic; } ;

/* Variables and functions */
 scalar_t__ RXE_ATOMIC_MASK ; 
 scalar_t__ RXE_READ_MASK ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_qp*) ; 

void free_rd_atomic_resource(struct rxe_qp *qp, struct resp_res *res)
{
	if (res->type == RXE_ATOMIC_MASK) {
		rxe_drop_ref(qp);
		kfree_skb(res->atomic.skb);
	} else if (res->type == RXE_READ_MASK) {
		if (res->read.mr)
			rxe_drop_ref(res->read.mr);
	}
	res->type = 0;
}