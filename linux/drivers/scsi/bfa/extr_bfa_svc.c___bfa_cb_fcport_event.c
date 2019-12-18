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
struct bfa_fcport_ln_s {int /*<<< orphan*/  ln_event; TYPE_1__* fcport; } ;
typedef  scalar_t__ bfa_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  event_cbarg; int /*<<< orphan*/  (* event_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCPORT_LN_SM_NOTIFICATION ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcport_ln_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__bfa_cb_fcport_event(void *cbarg, bfa_boolean_t complete)
{
	struct bfa_fcport_ln_s *ln = cbarg;

	if (complete)
		ln->fcport->event_cbfn(ln->fcport->event_cbarg, ln->ln_event);
	else
		bfa_sm_send_event(ln, BFA_FCPORT_LN_SM_NOTIFICATION);
}