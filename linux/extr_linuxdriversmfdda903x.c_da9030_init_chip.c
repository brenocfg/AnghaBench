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
typedef  int /*<<< orphan*/  uint8_t ;
struct da903x_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9030_CHIP_ID ; 
 int /*<<< orphan*/  DA9030_SYS_CTRL_A ; 
 int __da903x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __da903x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9030_init_chip(struct da903x_chip *chip)
{
	uint8_t chip_id;
	int err;

	err = __da903x_read(chip->client, DA9030_CHIP_ID, &chip_id);
	if (err)
		return err;

	err = __da903x_write(chip->client, DA9030_SYS_CTRL_A, 0xE8);
	if (err)
		return err;

	dev_info(chip->dev, "DA9030 (CHIP ID: 0x%02x) detected\n", chip_id);
	return 0;
}