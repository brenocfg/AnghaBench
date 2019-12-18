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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  e3; int /*<<< orphan*/  e2; int /*<<< orphan*/  e1h; int /*<<< orphan*/  e1; } ;
struct TYPE_4__ {TYPE_1__ reg_mask; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1H (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E2 (struct bnx2x*) ; 
 TYPE_2__* bnx2x_blocks_parity_data ; 

__attribute__((used)) static inline u32 bnx2x_parity_reg_mask(struct bnx2x *bp, int idx)
{
	if (CHIP_IS_E1(bp))
		return bnx2x_blocks_parity_data[idx].reg_mask.e1;
	else if (CHIP_IS_E1H(bp))
		return bnx2x_blocks_parity_data[idx].reg_mask.e1h;
	else if (CHIP_IS_E2(bp))
		return bnx2x_blocks_parity_data[idx].reg_mask.e2;
	else /* CHIP_IS_E3 */
		return bnx2x_blocks_parity_data[idx].reg_mask.e3;
}