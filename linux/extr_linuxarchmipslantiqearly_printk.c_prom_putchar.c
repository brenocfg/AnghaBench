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
 int /*<<< orphan*/  LTQ_ASC_FSTAT ; 
 int /*<<< orphan*/  LTQ_ASC_TBUF ; 
 int TXMASK ; 
 int TXOFFSET ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int ltq_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_w8 (char,int /*<<< orphan*/ ) ; 

void prom_putchar(char c)
{
	unsigned long flags;

	local_irq_save(flags);
	do { } while ((ltq_r32(LTQ_ASC_FSTAT) & TXMASK) >> TXOFFSET);
	if (c == '\n')
		ltq_w8('\r', LTQ_ASC_TBUF);
	ltq_w8(c, LTQ_ASC_TBUF);
	local_irq_restore(flags);
}