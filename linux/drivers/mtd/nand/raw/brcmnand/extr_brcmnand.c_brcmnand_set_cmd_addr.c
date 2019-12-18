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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct brcmnand_host {int cs; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_CMD_ADDRESS ; 
 int /*<<< orphan*/  BRCMNAND_CMD_EXT_ADDRESS ; 
 int /*<<< orphan*/  brcmnand_read_reg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmnand_write_reg (struct brcmnand_controller*,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void brcmnand_set_cmd_addr(struct mtd_info *mtd, u64 addr)
{
	struct nand_chip *chip =  mtd_to_nand(mtd);
	struct brcmnand_host *host = nand_get_controller_data(chip);
	struct brcmnand_controller *ctrl = host->ctrl;

	brcmnand_write_reg(ctrl, BRCMNAND_CMD_EXT_ADDRESS,
			   (host->cs << 16) | ((addr >> 32) & 0xffff));
	(void)brcmnand_read_reg(ctrl, BRCMNAND_CMD_EXT_ADDRESS);
	brcmnand_write_reg(ctrl, BRCMNAND_CMD_ADDRESS,
			   lower_32_bits(addr));
	(void)brcmnand_read_reg(ctrl, BRCMNAND_CMD_ADDRESS);
}