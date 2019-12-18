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
struct bfa_rport_s {int /*<<< orphan*/  qe; } ;
struct bfa_rport_mod_s {int /*<<< orphan*/  rp_active_q; int /*<<< orphan*/  rp_free_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct bfa_rport_s**) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bfa_rport_s *
bfa_rport_alloc(struct bfa_rport_mod_s *mod)
{
	struct bfa_rport_s *rport;

	bfa_q_deq(&mod->rp_free_q, &rport);
	if (rport)
		list_add_tail(&rport->qe, &mod->rp_active_q);

	return rport;
}