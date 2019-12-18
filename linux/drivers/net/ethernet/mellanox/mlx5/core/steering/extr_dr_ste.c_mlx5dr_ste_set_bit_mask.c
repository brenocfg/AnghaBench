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
typedef  int /*<<< orphan*/  u8 ;
struct dr_hw_ste_format {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SIZE_MASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlx5dr_ste_set_bit_mask(u8 *hw_ste_p, u8 *bit_mask)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;

	memcpy(hw_ste->mask, bit_mask, DR_STE_SIZE_MASK);
}