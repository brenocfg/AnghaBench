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
struct TYPE_2__ {int /*<<< orphan*/  cb_reqd; } ;
struct bfa_s {TYPE_1__ iocfc; int /*<<< orphan*/  plog; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_PL_EID_MISC ; 
 int /*<<< orphan*/  BFA_PL_MID_HAL ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  IOCFC_E_ENABLE ; 
 int /*<<< orphan*/  bfa_fsm_send_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_plog_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
bfa_iocfc_enable(struct bfa_s *bfa)
{
	bfa_plog_str(bfa->plog, BFA_PL_MID_HAL, BFA_PL_EID_MISC, 0,
		     "IOC Enable");
	bfa->iocfc.cb_reqd = BFA_TRUE;
	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_ENABLE);
}