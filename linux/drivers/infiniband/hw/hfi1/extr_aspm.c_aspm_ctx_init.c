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
struct hfi1_ctxtdata {int aspm_intr_supported; scalar_t__ ctxt; TYPE_1__* dd; int /*<<< orphan*/  aspm_timer; int /*<<< orphan*/  aspm_lock; } ;
struct TYPE_2__ {scalar_t__ first_dyn_alloc_ctxt; scalar_t__ aspm_supported; } ;

/* Variables and functions */
 scalar_t__ ASPM_MODE_DYNAMIC ; 
 int /*<<< orphan*/  aspm_ctx_timer_function ; 
 scalar_t__ aspm_mode ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static  void aspm_ctx_init(struct hfi1_ctxtdata *rcd)
{
	spin_lock_init(&rcd->aspm_lock);
	timer_setup(&rcd->aspm_timer, aspm_ctx_timer_function, 0);
	rcd->aspm_intr_supported = rcd->dd->aspm_supported &&
		aspm_mode == ASPM_MODE_DYNAMIC &&
		rcd->ctxt < rcd->dd->first_dyn_alloc_ctxt;
}