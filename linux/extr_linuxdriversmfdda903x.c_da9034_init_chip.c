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
 int /*<<< orphan*/  DA9034_CHIP_ID ; 
 int DA9034_SYS_CTRL_A ; 
 int DA9034_SYS_CTRL_B ; 
 int __da903x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __da903x_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9034_init_chip(struct da903x_chip *chip)
{
	uint8_t chip_id;
	int err;

	err = __da903x_read(chip->client, DA9034_CHIP_ID, &chip_id);
	if (err)
		return err;

	err = __da903x_write(chip->client, DA9034_SYS_CTRL_A, 0xE8);
	if (err)
		return err;

	/* avoid SRAM power off during sleep*/
	__da903x_write(chip->client, 0x10, 0x07);
	__da903x_write(chip->client, 0x11, 0xff);
	__da903x_write(chip->client, 0x12, 0xff);

	/* Enable the ONKEY power down functionality */
	__da903x_write(chip->client, DA9034_SYS_CTRL_B, 0x20);
	__da903x_write(chip->client, DA9034_SYS_CTRL_A, 0x60);

	/* workaround to make LEDs work */
	__da903x_write(chip->client, 0x90, 0x01);
	__da903x_write(chip->client, 0xB0, 0x08);

	/* make ADTV1 and SDTV1 effective */
	__da903x_write(chip->client, 0x20, 0x00);

	dev_info(chip->dev, "DA9034 (CHIP ID: 0x%02x) detected\n", chip_id);
	return 0;
}