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
struct rxe_qp {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rxe_drop_index (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_qp_destroy (struct rxe_qp*) ; 
 struct rxe_qp* to_rqp (struct ib_qp*) ; 

__attribute__((used)) static int rxe_destroy_qp(struct ib_qp *ibqp, struct ib_udata *udata)
{
	struct rxe_qp *qp = to_rqp(ibqp);

	rxe_qp_destroy(qp);
	rxe_drop_index(qp);
	rxe_drop_ref(qp);
	return 0;
}