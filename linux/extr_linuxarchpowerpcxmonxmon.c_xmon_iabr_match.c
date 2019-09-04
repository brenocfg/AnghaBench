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
struct pt_regs {int msr; } ;

/* Variables and functions */
 int MSR_64BIT ; 
 int MSR_IR ; 
 int MSR_PR ; 
 int /*<<< orphan*/ * iabr ; 
 int /*<<< orphan*/  xmon_core (struct pt_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xmon_iabr_match(struct pt_regs *regs)
{
	if ((regs->msr & (MSR_IR|MSR_PR|MSR_64BIT)) != (MSR_IR|MSR_64BIT))
		return 0;
	if (iabr == NULL)
		return 0;
	xmon_core(regs, 0);
	return 1;
}