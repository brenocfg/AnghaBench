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
struct rxe_dev {int /*<<< orphan*/  tfm; int /*<<< orphan*/  mc_elem_pool; int /*<<< orphan*/  mc_grp_pool; int /*<<< orphan*/  mw_pool; int /*<<< orphan*/  mr_pool; int /*<<< orphan*/  cq_pool; int /*<<< orphan*/  qp_pool; int /*<<< orphan*/  srq_pool; int /*<<< orphan*/  ah_pool; int /*<<< orphan*/  pd_pool; int /*<<< orphan*/  uc_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_cleanup_ports (struct rxe_dev*) ; 
 int /*<<< orphan*/  rxe_pool_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxe_cleanup(struct rxe_dev *rxe)
{
	rxe_pool_cleanup(&rxe->uc_pool);
	rxe_pool_cleanup(&rxe->pd_pool);
	rxe_pool_cleanup(&rxe->ah_pool);
	rxe_pool_cleanup(&rxe->srq_pool);
	rxe_pool_cleanup(&rxe->qp_pool);
	rxe_pool_cleanup(&rxe->cq_pool);
	rxe_pool_cleanup(&rxe->mr_pool);
	rxe_pool_cleanup(&rxe->mw_pool);
	rxe_pool_cleanup(&rxe->mc_grp_pool);
	rxe_pool_cleanup(&rxe->mc_elem_pool);

	rxe_cleanup_ports(rxe);

	crypto_free_shash(rxe->tfm);
}