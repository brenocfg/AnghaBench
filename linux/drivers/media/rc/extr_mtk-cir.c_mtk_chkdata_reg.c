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
struct TYPE_2__ {int* regs; } ;

/* Variables and functions */
 size_t MTK_CHKDATA_REG ; 

__attribute__((used)) static inline u32 mtk_chkdata_reg(struct mtk_ir *ir, u32 i)
{
	return ir->data->regs[MTK_CHKDATA_REG] + 4 * i;
}