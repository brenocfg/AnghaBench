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
typedef  int u32 ;
struct mtk_ir {scalar_t__ base; } ;

/* Variables and functions */
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_w32_mask(struct mtk_ir *ir, u32 val, u32 mask, unsigned int reg)
{
	u32 tmp;

	tmp = __raw_readl(ir->base + reg);
	tmp = (tmp & ~mask) | val;
	__raw_writel(tmp, ir->base + reg);
}