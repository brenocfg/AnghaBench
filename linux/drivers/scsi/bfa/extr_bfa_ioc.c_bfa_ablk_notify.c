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
struct bfa_ablk_s {int /*<<< orphan*/  busy; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cbarg; int /*<<< orphan*/ * pcifn; int /*<<< orphan*/  ioc; } ;
typedef  enum bfa_ioc_event_e { ____Placeholder_bfa_ioc_event_e } bfa_ioc_event_e ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
#define  BFA_IOC_E_DISABLED 130 
#define  BFA_IOC_E_ENABLED 129 
#define  BFA_IOC_E_FAILED 128 
 int /*<<< orphan*/  BFA_STATUS_FAILED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ablk_notify(void *cbarg, enum bfa_ioc_event_e event)
{
	struct bfa_ablk_s *ablk = (struct bfa_ablk_s *)cbarg;

	bfa_trc(ablk->ioc, event);

	switch (event) {
	case BFA_IOC_E_ENABLED:
		WARN_ON(ablk->busy != BFA_FALSE);
		break;

	case BFA_IOC_E_DISABLED:
	case BFA_IOC_E_FAILED:
		/* Fail any pending requests */
		ablk->pcifn = NULL;
		if (ablk->busy) {
			if (ablk->cbfn)
				ablk->cbfn(ablk->cbarg, BFA_STATUS_FAILED);
			ablk->cbfn = NULL;
			ablk->busy = BFA_FALSE;
		}
		break;

	default:
		WARN_ON(1);
		break;
	}
}