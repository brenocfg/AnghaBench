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
struct bfa_sgpg_wqe_s {scalar_t__ nsgpg_total; scalar_t__ nsgpg; int /*<<< orphan*/  sgpg_q; int /*<<< orphan*/  qe; } ;
struct bfa_sgpg_mod_s {int /*<<< orphan*/  sgpg_wait_q; } ;
struct bfa_s {int dummy; } ;

/* Variables and functions */
 struct bfa_sgpg_mod_s* BFA_SGPG_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_q_is_on_q (int /*<<< orphan*/ *,struct bfa_sgpg_wqe_s*) ; 
 int /*<<< orphan*/  bfa_sgpg_mfree (struct bfa_s*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
bfa_sgpg_wcancel(struct bfa_s *bfa, struct bfa_sgpg_wqe_s *wqe)
{
	struct bfa_sgpg_mod_s *mod = BFA_SGPG_MOD(bfa);

	WARN_ON(!bfa_q_is_on_q(&mod->sgpg_wait_q, wqe));
	list_del(&wqe->qe);

	if (wqe->nsgpg_total != wqe->nsgpg)
		bfa_sgpg_mfree(bfa, &wqe->sgpg_q,
				   wqe->nsgpg_total - wqe->nsgpg);
}