#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lp55xx_chip {TYPE_1__* cl; struct firmware* fw; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int LP5562_PROGRAM_LENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lp5562_load_engine (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp5562_update_firmware (struct lp55xx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lp5562_firmware_loaded(struct lp55xx_chip *chip)
{
	const struct firmware *fw = chip->fw;

	/*
	 * the firmware is encoded in ascii hex character, with 2 chars
	 * per byte
	 */
	if (fw->size > (LP5562_PROGRAM_LENGTH * 2)) {
		dev_err(&chip->cl->dev, "firmware data size overflow: %zu\n",
			fw->size);
		return;
	}

	/*
	 * Program memory sequence
	 *  1) set engine mode to "LOAD"
	 *  2) write firmware data into program memory
	 */

	lp5562_load_engine(chip);
	lp5562_update_firmware(chip, fw->data, fw->size);
}