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
struct pt_regs {unsigned long cp0_epc; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 scalar_t__ dsemul_page () ; 

__attribute__((used)) static bool within_emuframe(struct pt_regs *regs)
{
	unsigned long base = (unsigned long)dsemul_page();

	if (regs->cp0_epc < base)
		return false;
	if (regs->cp0_epc >= (base + PAGE_SIZE))
		return false;

	return true;
}