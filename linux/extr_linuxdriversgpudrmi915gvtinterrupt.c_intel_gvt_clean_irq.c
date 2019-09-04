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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct intel_gvt_irq {TYPE_1__ vblank_timer; } ;
struct intel_gvt {struct intel_gvt_irq irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

void intel_gvt_clean_irq(struct intel_gvt *gvt)
{
	struct intel_gvt_irq *irq = &gvt->irq;

	hrtimer_cancel(&irq->vblank_timer.timer);
}