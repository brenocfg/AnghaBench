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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_DELTA_GPIO_PIN_NAND_ALE ; 
 int /*<<< orphan*/  AMS_DELTA_GPIO_PIN_NAND_CLE ; 
 int /*<<< orphan*/  AMS_DELTA_GPIO_PIN_NAND_NCE ; 
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_CTRL_CHANGE ; 
 unsigned int NAND_NCE ; 
 int /*<<< orphan*/  ams_delta_write_byte (struct mtd_info*,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ams_delta_hwcontrol(struct mtd_info *mtd, int cmd,
				unsigned int ctrl)
{

	if (ctrl & NAND_CTRL_CHANGE) {
		gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_NCE,
				(ctrl & NAND_NCE) == 0);
		gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_CLE,
				(ctrl & NAND_CLE) != 0);
		gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_ALE,
				(ctrl & NAND_ALE) != 0);
	}

	if (cmd != NAND_CMD_NONE)
		ams_delta_write_byte(mtd, cmd);
}