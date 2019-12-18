#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lps; } ;
struct bfa_fcs_s {int /*<<< orphan*/  wc; TYPE_1__ fabric; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_FABRIC_SM_DELETE ; 
 int /*<<< orphan*/  bfa_fcs_exit_comp ; 
 int /*<<< orphan*/  bfa_lps_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fcs_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_wc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_s*) ; 
 int /*<<< orphan*/  bfa_wc_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_wc_wait (int /*<<< orphan*/ *) ; 

void
bfa_fcs_exit(struct bfa_fcs_s *fcs)
{
	bfa_wc_init(&fcs->wc, bfa_fcs_exit_comp, fcs);
	bfa_wc_up(&fcs->wc);
	bfa_trc(fcs, 0);
	bfa_lps_delete(fcs->fabric.lps);
	bfa_sm_send_event(&fcs->fabric, BFA_FCS_FABRIC_SM_DELETE);
	bfa_wc_wait(&fcs->wc);
}