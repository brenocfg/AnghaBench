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
typedef  scalar_t__ u8 ;
struct fusb302_chip {int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  fusb302_log (struct fusb302_chip*,char*,scalar_t__,int) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fusb302_i2c_read(struct fusb302_chip *chip,
			    u8 address, u8 *data)
{
	int ret = 0;

	ret = i2c_smbus_read_byte_data(chip->i2c_client, address);
	*data = (u8)ret;
	if (ret < 0)
		fusb302_log(chip, "cannot read %02x, ret=%d", address, ret);

	return ret;
}