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
struct bfa_rport_info_s {scalar_t__ max_frmsz; } ;
struct bfa_rport_s {struct bfa_rport_info_s rport_info; int /*<<< orphan*/  rport_tag; int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_RPORT_SM_ONLINE ; 
 scalar_t__ FC_MIN_PDUSZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_rport_online(struct bfa_rport_s *rport, struct bfa_rport_info_s *rport_info)
{
	WARN_ON(rport_info->max_frmsz == 0);

	/*
	 * Some JBODs are seen to be not setting PDU size correctly in PLOGI
	 * responses. Default to minimum size.
	 */
	if (rport_info->max_frmsz == 0) {
		bfa_trc(rport->bfa, rport->rport_tag);
		rport_info->max_frmsz = FC_MIN_PDUSZ;
	}

	rport->rport_info = *rport_info;
	bfa_sm_send_event(rport, BFA_RPORT_SM_ONLINE);
}