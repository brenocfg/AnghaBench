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
struct allegro_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL5_MCU_RESET ; 
 int /*<<< orphan*/  AL5_MCU_RESET_MODE ; 
 int /*<<< orphan*/  AL5_MCU_RESET_MODE_SLEEP ; 
 int /*<<< orphan*/  AL5_MCU_RESET_SOFT ; 
 int allegro_mcu_wait_for_sleep (struct allegro_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allegro_mcu_reset(struct allegro_dev *dev)
{
	int err;

	err = regmap_write(dev->regmap,
			   AL5_MCU_RESET_MODE, AL5_MCU_RESET_MODE_SLEEP);
	if (err < 0)
		return err;

	err = regmap_write(dev->regmap, AL5_MCU_RESET, AL5_MCU_RESET_SOFT);
	if (err < 0)
		return err;

	return allegro_mcu_wait_for_sleep(dev);
}