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
struct TYPE_2__ {int /*<<< orphan*/  reset_stats_cbarg; int /*<<< orphan*/  (* reset_stats_cbfn ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  get_stats_cbarg; int /*<<< orphan*/  (* get_stats_cbfn ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  get_attr_cbarg; int /*<<< orphan*/  (* get_attr_cbfn ) (int /*<<< orphan*/ ,void*) ;} ;
struct bfa_cee_s {TYPE_1__ cbfn; void* reset_stats_pending; void* reset_stats_status; void* get_stats_pending; void* get_stats_status; void* get_attr_pending; void* get_attr_status; } ;
typedef  enum bfa_ioc_event_e { ____Placeholder_bfa_ioc_event_e } bfa_ioc_event_e ;

/* Variables and functions */
 void* BFA_FALSE ; 
#define  BFA_IOC_E_DISABLED 129 
#define  BFA_IOC_E_FAILED 128 
 void* BFA_STATUS_FAILED ; 
 void* BFA_TRUE ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_cee_s*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,void*) ; 

void
bfa_cee_notify(void *arg, enum bfa_ioc_event_e event)
{
	struct bfa_cee_s *cee = (struct bfa_cee_s *) arg;

	bfa_trc(cee, event);

	switch (event) {
	case BFA_IOC_E_DISABLED:
	case BFA_IOC_E_FAILED:
		if (cee->get_attr_pending == BFA_TRUE) {
			cee->get_attr_status = BFA_STATUS_FAILED;
			cee->get_attr_pending  = BFA_FALSE;
			if (cee->cbfn.get_attr_cbfn) {
				cee->cbfn.get_attr_cbfn(
					cee->cbfn.get_attr_cbarg,
					BFA_STATUS_FAILED);
			}
		}
		if (cee->get_stats_pending == BFA_TRUE) {
			cee->get_stats_status = BFA_STATUS_FAILED;
			cee->get_stats_pending  = BFA_FALSE;
			if (cee->cbfn.get_stats_cbfn) {
				cee->cbfn.get_stats_cbfn(
				cee->cbfn.get_stats_cbarg,
				BFA_STATUS_FAILED);
			}
		}
		if (cee->reset_stats_pending == BFA_TRUE) {
			cee->reset_stats_status = BFA_STATUS_FAILED;
			cee->reset_stats_pending  = BFA_FALSE;
			if (cee->cbfn.reset_stats_cbfn) {
				cee->cbfn.reset_stats_cbfn(
				cee->cbfn.reset_stats_cbarg,
				BFA_STATUS_FAILED);
			}
		}
		break;

	default:
		break;
	}
}