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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct gpmi_nand_data {int* cmd_buffer; scalar_t__ command_length; int /*<<< orphan*/  current_chip; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int gpmi_send_command (struct gpmi_nand_data*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void gpmi_cmd_ctrl(struct mtd_info *mtd, int data, unsigned int ctrl)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct gpmi_nand_data *this = nand_get_controller_data(chip);
	int ret;

	/*
	 * Every operation begins with a command byte and a series of zero or
	 * more address bytes. These are distinguished by either the Address
	 * Latch Enable (ALE) or Command Latch Enable (CLE) signals being
	 * asserted. When MTD is ready to execute the command, it will deassert
	 * both latch enables.
	 *
	 * Rather than run a separate DMA operation for every single byte, we
	 * queue them up and run a single DMA operation for the entire series
	 * of command and data bytes. NAND_CMD_NONE means the END of the queue.
	 */
	if ((ctrl & (NAND_ALE | NAND_CLE))) {
		if (data != NAND_CMD_NONE)
			this->cmd_buffer[this->command_length++] = data;
		return;
	}

	if (!this->command_length)
		return;

	ret = gpmi_send_command(this);
	if (ret)
		dev_err(this->dev, "Chip: %u, Error %d\n",
			this->current_chip, ret);

	this->command_length = 0;
}