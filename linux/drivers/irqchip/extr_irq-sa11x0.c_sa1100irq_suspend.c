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
struct sa1100irq_state {int saved; int icmr; void* iccr; void* iclr; } ;

/* Variables and functions */
 scalar_t__ ICCR ; 
 scalar_t__ ICLR ; 
 scalar_t__ ICMR ; 
 scalar_t__ iobase ; 
 void* readl_relaxed (scalar_t__) ; 
 struct sa1100irq_state sa1100irq_state ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int sa1100irq_suspend(void)
{
	struct sa1100irq_state *st = &sa1100irq_state;

	st->saved = 1;
	st->icmr = readl_relaxed(iobase + ICMR);
	st->iclr = readl_relaxed(iobase + ICLR);
	st->iccr = readl_relaxed(iobase + ICCR);

	/*
	 * Disable all GPIO-based interrupts.
	 */
	writel_relaxed(st->icmr & 0xfffff000, iobase + ICMR);

	return 0;
}