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
struct i2c_diolan_u2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_I2C_PUT_BYTE_ACK ; 
 int diolan_usb_cmd_data (struct i2c_diolan_u2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int diolan_i2c_put_byte_ack(struct i2c_diolan_u2c *dev, u8 byte)
{
	return diolan_usb_cmd_data(dev, CMD_I2C_PUT_BYTE_ACK, byte, false);
}