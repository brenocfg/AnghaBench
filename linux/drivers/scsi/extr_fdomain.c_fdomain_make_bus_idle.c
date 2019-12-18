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
struct fdomain {scalar_t__ chip; scalar_t__ base; } ;

/* Variables and functions */
 int ACTL_CLRFIRQ ; 
 int ACTL_RESET ; 
 int PARITY_MASK ; 
 scalar_t__ REG_ACTL ; 
 scalar_t__ REG_BCTL ; 
 scalar_t__ REG_MCTL ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 scalar_t__ tmc18c30 ; 
 scalar_t__ tmc18c50 ; 

__attribute__((used)) static inline void fdomain_make_bus_idle(struct fdomain *fd)
{
	outb(0, fd->base + REG_BCTL);
	outb(0, fd->base + REG_MCTL);
	if (fd->chip == tmc18c50 || fd->chip == tmc18c30)
		/* Clear forced intr. */
		outb(ACTL_RESET | ACTL_CLRFIRQ | PARITY_MASK,
		     fd->base + REG_ACTL);
	else
		outb(ACTL_RESET | PARITY_MASK, fd->base + REG_ACTL);
}