#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mtk_ir {TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 size_t MTK_IRINT_EN_REG ; 
 int mtk_r32 (struct mtk_ir*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_ir*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mtk_irq_disable(struct mtk_ir *ir, u32 mask)
{
	u32 val;

	val = mtk_r32(ir, ir->data->regs[MTK_IRINT_EN_REG]);
	mtk_w32(ir, val & ~mask, ir->data->regs[MTK_IRINT_EN_REG]);
}