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
struct bfa_ioim_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  reqq; int /*<<< orphan*/  fcpim; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_IOIM_SM_START ; 
 scalar_t__ bfa_fcpim_ioredirect_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioim_cb_profile_start (int /*<<< orphan*/ ,struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_itnim_get_reqq (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 

void
bfa_ioim_start(struct bfa_ioim_s *ioim)
{
	bfa_ioim_cb_profile_start(ioim->fcpim, ioim);

	/*
	 * Obtain the queue over which this request has to be issued
	 */
	ioim->reqq = bfa_fcpim_ioredirect_enabled(ioim->bfa) ?
			BFA_FALSE : bfa_itnim_get_reqq(ioim);

	bfa_sm_send_event(ioim, BFA_IOIM_SM_START);
}