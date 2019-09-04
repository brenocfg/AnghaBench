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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ppc_save_regs (struct pt_regs*) ; 
 int xmon_core (struct pt_regs*,int /*<<< orphan*/ ) ; 

int xmon(struct pt_regs *excp)
{
	struct pt_regs regs;

	if (excp == NULL) {
		ppc_save_regs(&regs);
		excp = &regs;
	}

	return xmon_core(excp, 0);
}