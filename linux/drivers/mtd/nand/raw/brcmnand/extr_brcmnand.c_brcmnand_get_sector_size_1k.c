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
typedef  int /*<<< orphan*/  u16 ;
struct brcmnand_host {int /*<<< orphan*/  cs; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_CS_ACC_CONTROL ; 
 int /*<<< orphan*/  brcmnand_cs_offset (struct brcmnand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmnand_sector_1k_shift (struct brcmnand_controller*) ; 
 int nand_readreg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmnand_get_sector_size_1k(struct brcmnand_host *host)
{
	struct brcmnand_controller *ctrl = host->ctrl;
	int shift = brcmnand_sector_1k_shift(ctrl);
	u16 acc_control_offs = brcmnand_cs_offset(ctrl, host->cs,
						  BRCMNAND_CS_ACC_CONTROL);

	if (shift < 0)
		return 0;

	return (nand_readreg(ctrl, acc_control_offs) >> shift) & 0x1;
}