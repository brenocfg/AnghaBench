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
struct intel_breadcrumbs {int /*<<< orphan*/  hangcheck; int /*<<< orphan*/  fake_irq; int /*<<< orphan*/  irq_enabled; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ use_fake_irq (struct intel_breadcrumbs*) ; 
 scalar_t__ wait_timeout () ; 

__attribute__((used)) static void enable_fake_irq(struct intel_breadcrumbs *b)
{
	/* Ensure we never sleep indefinitely */
	if (!b->irq_enabled || use_fake_irq(b))
		mod_timer(&b->fake_irq, jiffies + 1);
	else
		mod_timer(&b->hangcheck, wait_timeout());
}