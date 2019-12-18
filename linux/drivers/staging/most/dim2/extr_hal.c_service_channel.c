#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* dim2; } ;
struct TYPE_3__ {int /*<<< orphan*/  ACSR0; } ;

/* Variables and functions */
 scalar_t__ ADT ; 
 int const ADT1_DNE_BIT ; 
 int const ADT1_ERR_BIT ; 
 int const ADT1_RDY_BIT ; 
 int bit_mask (int const) ; 
 int dim2_read_ctr (scalar_t__,int) ; 
 int /*<<< orphan*/  dim2_write_ctr_mask (scalar_t__,int*,int*) ; 
 TYPE_2__ g ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool service_channel(u8 ch_addr, u8 idx)
{
	u8 const shift = idx * 16;
	u32 const adt1 = dim2_read_ctr(ADT + ch_addr, 1);
	u32 mask[4] = { 0, 0, 0, 0 };
	u32 adt_w[4] = { 0, 0, 0, 0 };

	if (((adt1 >> (ADT1_DNE_BIT + shift)) & 1) == 0)
		return false;

	mask[1] =
		bit_mask(ADT1_DNE_BIT + shift) |
		bit_mask(ADT1_ERR_BIT + shift) |
		bit_mask(ADT1_RDY_BIT + shift);
	dim2_write_ctr_mask(ADT + ch_addr, mask, adt_w);

	/* clear channel status bit */
	writel(bit_mask(ch_addr), &g.dim2->ACSR0);

	return true;
}