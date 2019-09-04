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
 int VPDMA_MAX_SIZE1 ; 
 int VPDMA_MAX_SIZE2 ; 
 int VPDMA_MAX_SIZE3 ; 
 int /*<<< orphan*/  VPDMA_MAX_SIZE_HEIGHT_MASK ; 
 int /*<<< orphan*/  VPDMA_MAX_SIZE_HEIGHT_SHFT ; 
 int /*<<< orphan*/  VPDMA_MAX_SIZE_WIDTH_MASK ; 
 int /*<<< orphan*/  VPDMA_MAX_SIZE_WIDTH_SHFT ; 
 int /*<<< orphan*/  write_field_reg (struct vpdma_data*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vpdma_set_max_size(struct vpdma_data *vpdma, int reg_addr,
			u32 width, u32 height)
{
	if (reg_addr != VPDMA_MAX_SIZE1 && reg_addr != VPDMA_MAX_SIZE2 &&
	    reg_addr != VPDMA_MAX_SIZE3)
		reg_addr = VPDMA_MAX_SIZE1;

	write_field_reg(vpdma, reg_addr, width - 1,
			VPDMA_MAX_SIZE_WIDTH_MASK, VPDMA_MAX_SIZE_WIDTH_SHFT);

	write_field_reg(vpdma, reg_addr, height - 1,
			VPDMA_MAX_SIZE_HEIGHT_MASK, VPDMA_MAX_SIZE_HEIGHT_SHFT);

}