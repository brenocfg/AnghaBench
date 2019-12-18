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
typedef  int u64 ;
struct brcmnand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_UNCORR_ADDR ; 
 int /*<<< orphan*/  BRCMNAND_UNCORR_EXT_ADDR ; 
 int brcmnand_read_reg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 brcmnand_get_uncorrecc_addr(struct brcmnand_controller *ctrl)
{
	u64 err_addr;

	err_addr = brcmnand_read_reg(ctrl, BRCMNAND_UNCORR_ADDR);
	err_addr |= ((u64)(brcmnand_read_reg(ctrl,
					     BRCMNAND_UNCORR_EXT_ADDR)
					     & 0xffff) << 32);

	return err_addr;
}