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
 int read_reg (struct vpdma_data*,int) ; 
 int /*<<< orphan*/  write_reg (struct vpdma_data*,int,int) ; 

__attribute__((used)) static void write_field_reg(struct vpdma_data *vpdma, int offset, u32 field,
		u32 mask, int shift)
{
	u32 val = read_reg(vpdma, offset);

	val &= ~(mask << shift);
	val |= (field & mask) << shift;

	write_reg(vpdma, offset, val);
}