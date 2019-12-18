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
typedef  int /*<<< orphan*/  u8 ;
struct fusb302_chip {int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  fusb302_log (struct fusb302_chip*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fusb302_i2c_write(struct fusb302_chip *chip,
			     u8 address, u8 data)
{
	int ret = 0;

	ret = i2c_smbus_write_byte_data(chip->i2c_client, address, data);
	if (ret < 0)
		fusb302_log(chip, "cannot write 0x%02x to 0x%02x, ret=%d",
			    data, address, ret);

	return ret;
}