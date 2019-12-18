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
struct brcmnand_controller {int nand_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_CORR_COUNT ; 
 int brcmnand_read_reg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 brcmnand_count_corrected(struct brcmnand_controller *ctrl)
{
	if (ctrl->nand_version < 0x0600)
		return 1;
	return brcmnand_read_reg(ctrl, BRCMNAND_CORR_COUNT);
}