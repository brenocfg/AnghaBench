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
typedef  int uint32_t ;
struct socrates_nand_host {int /*<<< orphan*/  io_base; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int FPGA_NAND_CMD_ADDR ; 
 int FPGA_NAND_CMD_COMMAND ; 
 int FPGA_NAND_DATA_SHIFT ; 
 int FPGA_NAND_ENABLE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_NCE ; 
 struct socrates_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void socrates_nand_cmd_ctrl(struct nand_chip *nand_chip, int cmd,
				   unsigned int ctrl)
{
	struct socrates_nand_host *host = nand_get_controller_data(nand_chip);
	uint32_t val;

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		val = FPGA_NAND_CMD_COMMAND;
	else
		val = FPGA_NAND_CMD_ADDR;

	if (ctrl & NAND_NCE)
		val |= FPGA_NAND_ENABLE;

	val |= (cmd & 0xff) << FPGA_NAND_DATA_SHIFT;

	out_be32(host->io_base, val);
}