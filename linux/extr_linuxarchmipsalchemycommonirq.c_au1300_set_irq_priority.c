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

/* Variables and functions */
 scalar_t__ ALCHEMY_GPIC_INT_BASE ; 
 int /*<<< orphan*/  GPIC_CFG_IL_MASK ; 
 int /*<<< orphan*/  GPIC_CFG_IL_SET (int) ; 
 int /*<<< orphan*/  au1300_gpic_chgcfg (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void au1300_set_irq_priority(unsigned int irq, int p)
{
	irq -= ALCHEMY_GPIC_INT_BASE;
	au1300_gpic_chgcfg(irq, GPIC_CFG_IL_MASK, GPIC_CFG_IL_SET(p));
}