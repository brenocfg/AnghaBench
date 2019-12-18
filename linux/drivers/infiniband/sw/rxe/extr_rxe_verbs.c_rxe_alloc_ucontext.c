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
struct rxe_ucontext {int /*<<< orphan*/  pelem; } ;
struct rxe_dev {int /*<<< orphan*/  uc_pool; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int rxe_add_to_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 
 struct rxe_ucontext* to_ruc (struct ib_ucontext*) ; 

__attribute__((used)) static int rxe_alloc_ucontext(struct ib_ucontext *uctx, struct ib_udata *udata)
{
	struct rxe_dev *rxe = to_rdev(uctx->device);
	struct rxe_ucontext *uc = to_ruc(uctx);

	return rxe_add_to_pool(&rxe->uc_pool, &uc->pelem);
}