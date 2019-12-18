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
struct bfa_ioc {int /*<<< orphan*/  bfa; TYPE_1__* cbfn; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hbfail_cbfn ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOC_E_FAILED ; 
 int /*<<< orphan*/  bfa_ioc_event_notify (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_debug_save_ftrc (struct bfa_ioc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_fail_notify(struct bfa_ioc *ioc)
{
	/**
	 * Notify driver and common modules registered for notification.
	 */
	ioc->cbfn->hbfail_cbfn(ioc->bfa);
	bfa_ioc_event_notify(ioc, BFA_IOC_E_FAILED);
	bfa_nw_ioc_debug_save_ftrc(ioc);
}