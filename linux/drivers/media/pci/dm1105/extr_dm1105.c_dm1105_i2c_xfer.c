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
struct i2c_msg {int flags; int addr; int len; int* buf; } ;
struct i2c_adapter {struct dm1105_dev* algo_data; } ;
struct dm1105_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ DM1105_I2CCTR ; 
 scalar_t__ DM1105_I2CDAT ; 
 scalar_t__ DM1105_I2CSTS ; 
 int I2C_M_RD ; 
 int dm_readb (scalar_t__) ; 
 int /*<<< orphan*/  dm_writeb (scalar_t__,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int dm1105_i2c_xfer(struct i2c_adapter *i2c_adap,
			    struct i2c_msg *msgs, int num)
{
	struct dm1105_dev *dev ;

	int addr, rc, i, j, k, len, byte, data;
	u8 status;

	dev = i2c_adap->algo_data;
	for (i = 0; i < num; i++) {
		dm_writeb(DM1105_I2CCTR, 0x00);
		if (msgs[i].flags & I2C_M_RD) {
			/* read bytes */
			addr  = msgs[i].addr << 1;
			addr |= 1;
			dm_writeb(DM1105_I2CDAT, addr);
			for (byte = 0; byte < msgs[i].len; byte++)
				dm_writeb(DM1105_I2CDAT + byte + 1, 0);

			dm_writeb(DM1105_I2CCTR, 0x81 + msgs[i].len);
			for (j = 0; j < 55; j++) {
				mdelay(10);
				status = dm_readb(DM1105_I2CSTS);
				if ((status & 0xc0) == 0x40)
					break;
			}
			if (j >= 55)
				return -1;

			for (byte = 0; byte < msgs[i].len; byte++) {
				rc = dm_readb(DM1105_I2CDAT + byte + 1);
				if (rc < 0)
					goto err;
				msgs[i].buf[byte] = rc;
			}
		} else if ((msgs[i].buf[0] == 0xf7) && (msgs[i].addr == 0x55)) {
			/* prepared for cx24116 firmware */
			/* Write in small blocks */
			len = msgs[i].len - 1;
			k = 1;
			do {
				dm_writeb(DM1105_I2CDAT, msgs[i].addr << 1);
				dm_writeb(DM1105_I2CDAT + 1, 0xf7);
				for (byte = 0; byte < (len > 48 ? 48 : len); byte++) {
					data = msgs[i].buf[k + byte];
					dm_writeb(DM1105_I2CDAT + byte + 2, data);
				}
				dm_writeb(DM1105_I2CCTR, 0x82 + (len > 48 ? 48 : len));
				for (j = 0; j < 25; j++) {
					mdelay(10);
					status = dm_readb(DM1105_I2CSTS);
					if ((status & 0xc0) == 0x40)
						break;
				}

				if (j >= 25)
					return -1;

				k += 48;
				len -= 48;
			} while (len > 0);
		} else {
			/* write bytes */
			dm_writeb(DM1105_I2CDAT, msgs[i].addr << 1);
			for (byte = 0; byte < msgs[i].len; byte++) {
				data = msgs[i].buf[byte];
				dm_writeb(DM1105_I2CDAT + byte + 1, data);
			}
			dm_writeb(DM1105_I2CCTR, 0x81 + msgs[i].len);
			for (j = 0; j < 25; j++) {
				mdelay(10);
				status = dm_readb(DM1105_I2CSTS);
				if ((status & 0xc0) == 0x40)
					break;
			}

			if (j >= 25)
				return -1;
		}
	}
	return num;
 err:
	return rc;
}