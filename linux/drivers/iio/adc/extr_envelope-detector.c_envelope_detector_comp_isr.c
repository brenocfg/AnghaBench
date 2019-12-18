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
struct envelope {int comp; int /*<<< orphan*/  comp_lock; int /*<<< orphan*/  comp_irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t envelope_detector_comp_isr(int irq, void *ctx)
{
	struct envelope *env = ctx;

	spin_lock(&env->comp_lock);
	env->comp = 1;
	disable_irq_nosync(env->comp_irq);
	spin_unlock(&env->comp_lock);

	return IRQ_HANDLED;
}