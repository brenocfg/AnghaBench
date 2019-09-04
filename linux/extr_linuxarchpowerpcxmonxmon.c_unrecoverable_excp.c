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
 int MSR_RI ; 

__attribute__((used)) static inline int unrecoverable_excp(struct pt_regs *regs)
{
#if defined(CONFIG_4xx) || defined(CONFIG_PPC_BOOK3E)
	/* We have no MSR_RI bit on 4xx or Book3e, so we simply return false */
	return 0;
#else
	return ((regs->msr & MSR_RI) == 0);
#endif
}