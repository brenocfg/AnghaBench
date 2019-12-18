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
struct sti_tvout {int dummy; } ;

/* Variables and functions */
 int TVO_VIP_REORDER_B_SHIFT ; 
 int TVO_VIP_REORDER_G_SHIFT ; 
 int TVO_VIP_REORDER_MASK ; 
 int TVO_VIP_REORDER_R_SHIFT ; 
 int tvout_read (struct sti_tvout*,int) ; 
 int /*<<< orphan*/  tvout_write (struct sti_tvout*,int,int) ; 

__attribute__((used)) static void tvout_vip_set_color_order(struct sti_tvout *tvout, int reg,
				      u32 cr_r, u32 y_g, u32 cb_b)
{
	u32 val = tvout_read(tvout, reg);

	val &= ~(TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_R_SHIFT);
	val &= ~(TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_G_SHIFT);
	val &= ~(TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_B_SHIFT);
	val |= cr_r << TVO_VIP_REORDER_R_SHIFT;
	val |= y_g << TVO_VIP_REORDER_G_SHIFT;
	val |= cb_b << TVO_VIP_REORDER_B_SHIFT;

	tvout_write(tvout, val, reg);
}