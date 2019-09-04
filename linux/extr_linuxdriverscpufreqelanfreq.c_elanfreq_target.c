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
struct cpufreq_policy {int dummy; } ;
struct TYPE_2__ {int val80h; int val40h; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CSCDR ; 
 int /*<<< orphan*/  REG_CSCIR ; 
 TYPE_1__* elan_multiplier ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int elanfreq_target(struct cpufreq_policy *policy,
			    unsigned int state)
{
	/*
	 * Access to the Elan's internal registers is indexed via
	 * 0x22: Chip Setup & Control Register Index Register (CSCI)
	 * 0x23: Chip Setup & Control Register Data  Register (CSCD)
	 *
	 */

	/*
	 * 0x40 is the Power Management Unit's Force Mode Register.
	 * Bit 6 enables Hyperspeed Mode (66/100 MHz core frequency)
	 */

	local_irq_disable();
	outb_p(0x40, REG_CSCIR);		/* Disable hyperspeed mode */
	outb_p(0x00, REG_CSCDR);
	local_irq_enable();		/* wait till internal pipelines and */
	udelay(1000);			/* buffers have cleaned up          */

	local_irq_disable();

	/* now, set the CPU clock speed register (0x80) */
	outb_p(0x80, REG_CSCIR);
	outb_p(elan_multiplier[state].val80h, REG_CSCDR);

	/* now, the hyperspeed bit in PMU Force Mode Register (0x40) */
	outb_p(0x40, REG_CSCIR);
	outb_p(elan_multiplier[state].val40h, REG_CSCDR);
	udelay(10000);
	local_irq_enable();

	return 0;
}