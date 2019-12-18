#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lock; void* status; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_3__ {int lock; void* status; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,void*) ;} ;
struct bfa_diag_s {int block; void* status; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  timer_active; int /*<<< orphan*/  timer; TYPE_2__ tsensor; TYPE_1__ fwping; } ;
typedef  enum bfa_ioc_event_e { ____Placeholder_bfa_ioc_event_e } bfa_ioc_event_e ;

/* Variables and functions */
#define  BFA_IOC_E_DISABLED 129 
#define  BFA_IOC_E_FAILED 128 
 void* BFA_STATUS_IOC_FAILURE ; 
 int /*<<< orphan*/  bfa_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_diag_s*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
bfa_diag_notify(void *diag_arg, enum bfa_ioc_event_e event)
{
	struct bfa_diag_s *diag = diag_arg;

	bfa_trc(diag, event);
	bfa_trc(diag, diag->block);
	bfa_trc(diag, diag->fwping.lock);
	bfa_trc(diag, diag->tsensor.lock);

	switch (event) {
	case BFA_IOC_E_DISABLED:
	case BFA_IOC_E_FAILED:
		if (diag->fwping.lock) {
			diag->fwping.status = BFA_STATUS_IOC_FAILURE;
			diag->fwping.cbfn(diag->fwping.cbarg,
					diag->fwping.status);
			diag->fwping.lock = 0;
		}

		if (diag->tsensor.lock) {
			diag->tsensor.status = BFA_STATUS_IOC_FAILURE;
			diag->tsensor.cbfn(diag->tsensor.cbarg,
					   diag->tsensor.status);
			diag->tsensor.lock = 0;
		}

		if (diag->block) {
			if (diag->timer_active) {
				bfa_timer_stop(&diag->timer);
				diag->timer_active = 0;
			}

			diag->status = BFA_STATUS_IOC_FAILURE;
			diag->cbfn(diag->cbarg, diag->status);
			diag->block = 0;
		}
		break;

	default:
		break;
	}
}