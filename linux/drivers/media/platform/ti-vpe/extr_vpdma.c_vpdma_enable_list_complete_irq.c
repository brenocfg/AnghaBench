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
struct vpdma_data {int dummy; } ;

/* Variables and functions */
 int VPDMA_INTX_OFFSET ; 
 int VPDMA_INT_LIST0_MASK ; 
 int read_reg (struct vpdma_data*,int) ; 
 int /*<<< orphan*/  write_reg (struct vpdma_data*,int,int) ; 

void vpdma_enable_list_complete_irq(struct vpdma_data *vpdma, int irq_num,
		int list_num, bool enable)
{
	u32 reg_addr = VPDMA_INT_LIST0_MASK + VPDMA_INTX_OFFSET * irq_num;
	u32 val;

	val = read_reg(vpdma, reg_addr);
	if (enable)
		val |= (1 << (list_num * 2));
	else
		val &= ~(1 << (list_num * 2));
	write_reg(vpdma, reg_addr, val);
}