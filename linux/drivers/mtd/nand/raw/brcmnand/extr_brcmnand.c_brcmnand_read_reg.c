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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct brcmnand_controller {scalar_t__* reg_offsets; } ;
typedef  enum brcmnand_reg { ____Placeholder_brcmnand_reg } brcmnand_reg ;

/* Variables and functions */
 int /*<<< orphan*/  nand_readreg (struct brcmnand_controller*,scalar_t__) ; 

__attribute__((used)) static inline u32 brcmnand_read_reg(struct brcmnand_controller *ctrl,
		enum brcmnand_reg reg)
{
	u16 offs = ctrl->reg_offsets[reg];

	if (offs)
		return nand_readreg(ctrl, offs);
	else
		return 0;
}