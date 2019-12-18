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
struct bfa_s {int dummy; } ;
struct bfa_rport_s {int /*<<< orphan*/  stats; void* rport_drv; struct bfa_s* bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_RPORT_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  BFA_RPORT_SM_CREATE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct bfa_rport_s* bfa_rport_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_rport_sm_uninit ; 
 int /*<<< orphan*/  bfa_sm_cmp_state (struct bfa_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct bfa_rport_s *
bfa_rport_create(struct bfa_s *bfa, void *rport_drv)
{
	struct bfa_rport_s *rp;

	rp = bfa_rport_alloc(BFA_RPORT_MOD(bfa));

	if (rp == NULL)
		return NULL;

	rp->bfa = bfa;
	rp->rport_drv = rport_drv;
	memset(&rp->stats, 0, sizeof(rp->stats));

	WARN_ON(!bfa_sm_cmp_state(rp, bfa_rport_sm_uninit));
	bfa_sm_send_event(rp, BFA_RPORT_SM_CREATE);

	return rp;
}