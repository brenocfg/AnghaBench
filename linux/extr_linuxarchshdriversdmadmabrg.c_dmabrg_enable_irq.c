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
 int /*<<< orphan*/  DMABRGCR ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmabrg_enable_irq(unsigned int dmairq)
{
	unsigned long dcr;
	dcr = __raw_readl(DMABRGCR);
	dcr |= (1 << ((dmairq > 1) ? dmairq + 22 : dmairq + 8));
	__raw_writel(dcr, DMABRGCR);
}