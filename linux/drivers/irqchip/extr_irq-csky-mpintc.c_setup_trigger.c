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

/* Variables and functions */
 int /*<<< orphan*/  TRIG_BASE (unsigned long) ; 
 unsigned int TRIG_VAL (unsigned long,unsigned long) ; 
 unsigned int TRIG_VAL_MSK (unsigned long) ; 
 unsigned int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_trigger(unsigned long irq, unsigned long trigger)
{
	unsigned int tmp;

	spin_lock(&setup_lock);

	/* setup trigger */
	tmp = readl_relaxed(TRIG_BASE(irq)) & TRIG_VAL_MSK(irq);

	writel_relaxed(tmp | TRIG_VAL(trigger, irq), TRIG_BASE(irq));

	spin_unlock(&setup_lock);
}