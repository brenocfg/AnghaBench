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
typedef  int u16 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int af9005_read_ofdm_register (struct dvb_usb_device*,int /*<<< orphan*/ ,int*) ; 
 int af9005_usb_write_tuner_registers (struct dvb_usb_device*,int,int*,int) ; 
 int af9005_write_register_bits (struct dvb_usb_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int i2c_m_status_wdat_done_len ; 
 int i2c_m_status_wdat_done_pos ; 
 int i2c_m_status_wdat_fail_len ; 
 int i2c_m_status_wdat_fail_pos ; 
 int /*<<< orphan*/  msleep (int) ; 
 int* regmask ; 
 int /*<<< orphan*/  xd_I2C_i2c_m_status_wdat_done ; 
 int /*<<< orphan*/  xd_I2C_i2c_m_status_wdat_fail ; 

int af9005_write_tuner_registers(struct dvb_usb_device *d, u16 reg,
				 u8 * values, int len)
{
	/* don't let the name of this function mislead you: it's just used
	   as an interface from the firmware to the i2c bus. The actual
	   i2c addresses are contained in the data */
	int ret, i, done = 0, fail = 0;
	u8 temp;
	ret = af9005_usb_write_tuner_registers(d, reg, values, len);
	if (ret)
		return ret;
	if (reg != 0xffff) {
		/* check if write done (0xa40d bit 1) or fail (0xa40d bit 2) */
		for (i = 0; i < 200; i++) {
			ret =
			    af9005_read_ofdm_register(d,
						      xd_I2C_i2c_m_status_wdat_done,
						      &temp);
			if (ret)
				return ret;
			done = temp & (regmask[i2c_m_status_wdat_done_len - 1]
				       << i2c_m_status_wdat_done_pos);
			if (done)
				break;
			fail = temp & (regmask[i2c_m_status_wdat_fail_len - 1]
				       << i2c_m_status_wdat_fail_pos);
			if (fail)
				break;
			msleep(50);
		}
		if (i == 200)
			return -ETIMEDOUT;
		if (fail) {
			/* clear write fail bit */
			af9005_write_register_bits(d,
						   xd_I2C_i2c_m_status_wdat_fail,
						   i2c_m_status_wdat_fail_pos,
						   i2c_m_status_wdat_fail_len,
						   1);
			return -EIO;
		}
		/* clear write done bit */
		ret =
		    af9005_write_register_bits(d,
					       xd_I2C_i2c_m_status_wdat_fail,
					       i2c_m_status_wdat_done_pos,
					       i2c_m_status_wdat_done_len, 1);
		if (ret)
			return ret;
	}
	return 0;
}