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
struct brcmnand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_CORR_ADDR ; 
 int /*<<< orphan*/  BRCMNAND_CORR_EXT_ADDR ; 
 int /*<<< orphan*/  BRCMNAND_UNCORR_ADDR ; 
 int /*<<< orphan*/  BRCMNAND_UNCORR_EXT_ADDR ; 
 int /*<<< orphan*/  brcmnand_write_reg (struct brcmnand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmnand_clear_ecc_addr(struct brcmnand_controller *ctrl)
{

	/* Clear error addresses */
	brcmnand_write_reg(ctrl, BRCMNAND_UNCORR_ADDR, 0);
	brcmnand_write_reg(ctrl, BRCMNAND_CORR_ADDR, 0);
	brcmnand_write_reg(ctrl, BRCMNAND_UNCORR_EXT_ADDR, 0);
	brcmnand_write_reg(ctrl, BRCMNAND_CORR_EXT_ADDR, 0);
}