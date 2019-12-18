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
struct rxe_mem {struct rxe_mem* pd; int /*<<< orphan*/  state; } ;
struct ib_udata {int dummy; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXE_MEM_STATE_ZOMBIE ; 
 int /*<<< orphan*/  rxe_drop_index (struct rxe_mem*) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_mem*) ; 
 struct rxe_mem* to_rmr (struct ib_mr*) ; 

__attribute__((used)) static int rxe_dereg_mr(struct ib_mr *ibmr, struct ib_udata *udata)
{
	struct rxe_mem *mr = to_rmr(ibmr);

	mr->state = RXE_MEM_STATE_ZOMBIE;
	rxe_drop_ref(mr->pd);
	rxe_drop_index(mr);
	rxe_drop_ref(mr);
	return 0;
}