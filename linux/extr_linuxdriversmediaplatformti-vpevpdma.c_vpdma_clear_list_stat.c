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
typedef  scalar_t__ u32 ;
struct vpdma_data {int dummy; } ;

/* Variables and functions */
 int VPDMA_INTX_OFFSET ; 
 scalar_t__ VPDMA_INT_LIST0_STAT ; 
 int /*<<< orphan*/  write_reg (struct vpdma_data*,scalar_t__,int) ; 

void vpdma_clear_list_stat(struct vpdma_data *vpdma, int irq_num,
			   int list_num)
{
	u32 reg_addr = VPDMA_INT_LIST0_STAT + VPDMA_INTX_OFFSET * irq_num;

	write_reg(vpdma, reg_addr, 3 << (list_num * 2));
}