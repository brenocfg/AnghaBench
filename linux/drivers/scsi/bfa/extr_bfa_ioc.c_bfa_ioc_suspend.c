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
struct bfa_ioc_s {int /*<<< orphan*/  dbg_fwsave_once; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  IOC_E_HWERROR ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 

void
bfa_ioc_suspend(struct bfa_ioc_s *ioc)
{
	ioc->dbg_fwsave_once = BFA_TRUE;
	bfa_fsm_send_event(ioc, IOC_E_HWERROR);
}