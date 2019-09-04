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
struct sa1100irq_state {int /*<<< orphan*/  icmr; int /*<<< orphan*/  iclr; int /*<<< orphan*/  iccr; scalar_t__ saved; } ;

/* Variables and functions */
 scalar_t__ ICCR ; 
 scalar_t__ ICLR ; 
 scalar_t__ ICMR ; 
 scalar_t__ iobase ; 
 struct sa1100irq_state sa1100irq_state ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sa1100irq_resume(void)
{
	struct sa1100irq_state *st = &sa1100irq_state;

	if (st->saved) {
		writel_relaxed(st->iccr, iobase + ICCR);
		writel_relaxed(st->iclr, iobase + ICLR);

		writel_relaxed(st->icmr, iobase + ICMR);
	}
}