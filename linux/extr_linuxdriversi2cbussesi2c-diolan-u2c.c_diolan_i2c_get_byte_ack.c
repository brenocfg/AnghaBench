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
struct i2c_diolan_u2c {int /*<<< orphan*/ * ibuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_I2C_GET_BYTE_ACK ; 
 int EIO ; 
 int diolan_usb_cmd_data (struct i2c_diolan_u2c*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int diolan_i2c_get_byte_ack(struct i2c_diolan_u2c *dev, bool ack,
				   u8 *byte)
{
	int ret;

	ret = diolan_usb_cmd_data(dev, CMD_I2C_GET_BYTE_ACK, ack, true);
	if (ret > 0)
		*byte = dev->ibuffer[0];
	else if (ret == 0)
		ret = -EIO;

	return ret;
}