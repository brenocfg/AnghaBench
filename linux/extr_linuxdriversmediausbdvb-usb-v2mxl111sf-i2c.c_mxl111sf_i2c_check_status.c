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
typedef  int u8 ;
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
 int I2C_INT_STATUS_REG ; 
 int USB_END_I2C_CMD ; 
 int USB_READ_I2C_CMD ; 
 int /*<<< orphan*/  mxl111sf_i2c_get_data (struct mxl111sf_state*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  mxl_i2c_adv (char*) ; 

__attribute__((used)) static u8 mxl111sf_i2c_check_status(struct mxl111sf_state *state)
{
	u8 status = 0;
	u8 buf[26];

	mxl_i2c_adv("()");

	buf[0] = USB_READ_I2C_CMD;
	buf[1] = 0x00;

	buf[2] = I2C_INT_STATUS_REG;
	buf[3] = 0x00;
	buf[4] = 0x00;

	buf[5] = USB_END_I2C_CMD;

	mxl111sf_i2c_get_data(state, 0, buf, buf);

	if (buf[1] & 0x04)
		status = 1;

	return status;
}