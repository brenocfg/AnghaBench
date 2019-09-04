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
typedef  unsigned int u32 ;
struct mtk_cec {scalar_t__ regs; } ;

/* Variables and functions */
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mtk_cec_mask(struct mtk_cec *cec, unsigned int offset,
			 unsigned int val, unsigned int mask)
{
	u32 tmp = readl(cec->regs + offset) & ~mask;

	tmp |= val & mask;
	writel(val, cec->regs + offset);
}