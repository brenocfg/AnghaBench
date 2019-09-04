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
struct bfa_flash {int /*<<< orphan*/  op_busy; int /*<<< orphan*/  status; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  enum bfa_ioc_event { ____Placeholder_bfa_ioc_event } bfa_ioc_event ;

/* Variables and functions */
#define  BFA_IOC_E_DISABLED 129 
#define  BFA_IOC_E_FAILED 128 
 int /*<<< orphan*/  BFA_STATUS_IOC_FAILURE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_flash_notify(void *cbarg, enum bfa_ioc_event event)
{
	struct bfa_flash *flash = cbarg;

	switch (event) {
	case BFA_IOC_E_DISABLED:
	case BFA_IOC_E_FAILED:
		if (flash->op_busy) {
			flash->status = BFA_STATUS_IOC_FAILURE;
			flash->cbfn(flash->cbarg, flash->status);
			flash->op_busy = 0;
		}
		break;
	default:
		break;
	}
}