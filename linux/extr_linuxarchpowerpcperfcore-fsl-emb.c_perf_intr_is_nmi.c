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

__attribute__((used)) static inline int perf_intr_is_nmi(struct pt_regs *regs)
{
#ifdef __powerpc64__
	return (regs->softe & IRQS_DISABLED);
#else
	return 0;
#endif
}