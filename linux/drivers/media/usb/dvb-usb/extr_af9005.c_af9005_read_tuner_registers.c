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
typedef  scalar_t__ u16 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ APO_REG_I2C_RW_SILICON_TUNER ; 
 int ETIMEDOUT ; 
 int af9005_read_ofdm_register (struct dvb_usb_device*,int,int*) ; 
 int af9005_usb_read_tuner_registers (struct dvb_usb_device*,scalar_t__,int*,int) ; 
 int af9005_write_ofdm_register (struct dvb_usb_device*,int /*<<< orphan*/ ,int) ; 
 int af9005_write_tuner_registers (struct dvb_usb_device*,int,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  xd_I2C_i2c_m_data8 ; 

int af9005_read_tuner_registers(struct dvb_usb_device *d, u16 reg, u8 addr,
				u8 * values, int len)
{
	/* don't let the name of this function mislead you: it's just used
	   as an interface from the firmware to the i2c bus. The actual
	   i2c addresses are contained in the data */
	int ret, i;
	u8 temp, buf[2];

	buf[0] = addr;		/* tuner i2c address */
	buf[1] = values[0];	/* tuner register */

	values[0] = addr + 0x01;	/* i2c read address */

	if (reg == APO_REG_I2C_RW_SILICON_TUNER) {
		/* write tuner i2c address to tuner, 0c00c0 undocumented, found by sniffing */
		ret = af9005_write_tuner_registers(d, 0x00c0, buf, 2);
		if (ret)
			return ret;
	}

	/* send read command to ofsm */
	ret = af9005_usb_read_tuner_registers(d, reg, values, 1);
	if (ret)
		return ret;

	/* check if read done */
	for (i = 0; i < 200; i++) {
		ret = af9005_read_ofdm_register(d, 0xa408, &temp);
		if (ret)
			return ret;
		if (temp & 0x01)
			break;
		msleep(50);
	}
	if (i == 200)
		return -ETIMEDOUT;

	/* clear read done bit (by writing 1) */
	ret = af9005_write_ofdm_register(d, xd_I2C_i2c_m_data8, 1);
	if (ret)
		return ret;

	/* get read data (available from 0xa400) */
	for (i = 0; i < len; i++) {
		ret = af9005_read_ofdm_register(d, 0xa400 + i, &temp);
		if (ret)
			return ret;
		values[i] = temp;
	}
	return 0;
}