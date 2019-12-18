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
struct ps2if {scalar_t__ base; int /*<<< orphan*/  io; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PS2DATA ; 
 scalar_t__ PS2STAT ; 
 unsigned int PS2STAT_RXF ; 
 unsigned int PS2STAT_RXP ; 
 unsigned int PS2STAT_STP ; 
 unsigned int SERIO_FRAME ; 
 unsigned int SERIO_PARITY ; 
 int hweight8 (unsigned int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t ps2_rxint(int irq, void *dev_id)
{
	struct ps2if *ps2if = dev_id;
	unsigned int scancode, flag, status;

	status = readl_relaxed(ps2if->base + PS2STAT);
	while (status & PS2STAT_RXF) {
		if (status & PS2STAT_STP)
			writel_relaxed(PS2STAT_STP, ps2if->base + PS2STAT);

		flag = (status & PS2STAT_STP ? SERIO_FRAME : 0) |
		       (status & PS2STAT_RXP ? 0 : SERIO_PARITY);

		scancode = readl_relaxed(ps2if->base + PS2DATA) & 0xff;

		if (hweight8(scancode) & 1)
			flag ^= SERIO_PARITY;

		serio_interrupt(ps2if->io, scancode, flag);

		status = readl_relaxed(ps2if->base + PS2STAT);
        }

        return IRQ_HANDLED;
}