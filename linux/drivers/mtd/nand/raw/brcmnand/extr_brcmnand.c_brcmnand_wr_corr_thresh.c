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
struct brcmnand_host {int cs; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int nand_version; } ;
typedef  enum brcmnand_reg { ____Placeholder_brcmnand_reg } brcmnand_reg ;

/* Variables and functions */
 int BRCMNAND_CORR_THRESHOLD ; 
 int BRCMNAND_CORR_THRESHOLD_EXT ; 
 int /*<<< orphan*/  brcmnand_rmw_reg (struct brcmnand_controller*,int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmnand_wr_corr_thresh(struct brcmnand_host *host, u8 val)
{
	struct brcmnand_controller *ctrl = host->ctrl;
	unsigned int shift = 0, bits;
	enum brcmnand_reg reg = BRCMNAND_CORR_THRESHOLD;
	int cs = host->cs;

	if (ctrl->nand_version == 0x0702)
		bits = 7;
	else if (ctrl->nand_version >= 0x0600)
		bits = 6;
	else if (ctrl->nand_version >= 0x0500)
		bits = 5;
	else
		bits = 4;

	if (ctrl->nand_version >= 0x0702) {
		if (cs >= 4)
			reg = BRCMNAND_CORR_THRESHOLD_EXT;
		shift = (cs % 4) * bits;
	} else if (ctrl->nand_version >= 0x0600) {
		if (cs >= 5)
			reg = BRCMNAND_CORR_THRESHOLD_EXT;
		shift = (cs % 5) * bits;
	}
	brcmnand_rmw_reg(ctrl, reg, (bits - 1) << shift, shift, val);
}