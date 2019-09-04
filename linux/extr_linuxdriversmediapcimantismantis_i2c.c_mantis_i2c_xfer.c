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
typedef  int u32 ;
struct mantis_pci {int /*<<< orphan*/  i2c_lock; struct mantis_hwconfig* hwconfig; } ;
struct mantis_hwconfig {int i2c_mode; } ;
struct i2c_msg {int len; int flags; int addr; int* buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int I2C_M_RD ; 
 int MANTIS_BYTE_MODE ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  MANTIS_I2CDATA_CTL ; 
 int MANTIS_I2C_RATE_3 ; 
 int MANTIS_INT_I2CDONE ; 
 int MANTIS_INT_I2CRACK ; 
 int /*<<< orphan*/  MANTIS_INT_STAT ; 
 int TRIALS ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 struct mantis_pci* i2c_get_adapdata (struct i2c_adapter*) ; 
 int mantis_i2c_read (struct mantis_pci*,struct i2c_msg*) ; 
 int mantis_i2c_write (struct mantis_pci*,struct i2c_msg*) ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mantis_i2c_xfer(struct i2c_adapter *adapter, struct i2c_msg *msgs, int num)
{
	int ret = 0, i = 0, trials;
	u32 stat, data, txd;
	struct mantis_pci *mantis;
	struct mantis_hwconfig *config;

	mantis = i2c_get_adapdata(adapter);
	BUG_ON(!mantis);
	config = mantis->hwconfig;
	BUG_ON(!config);

	dprintk(MANTIS_DEBUG, 1, "Messages:%d", num);
	mutex_lock(&mantis->i2c_lock);

	while (i < num) {
		/* Byte MODE */
		if ((config->i2c_mode & MANTIS_BYTE_MODE) &&
		    ((i + 1) < num)			&&
		    (msgs[i].len < 2)			&&
		    (msgs[i + 1].len < 2)		&&
		    (msgs[i + 1].flags & I2C_M_RD)) {

			dprintk(MANTIS_DEBUG, 0, "        Byte MODE:\n");

			/* Read operation */
			txd = msgs[i].addr << 25 | (0x1 << 24)
						 | (msgs[i].buf[0] << 16)
						 | MANTIS_I2C_RATE_3;

			mmwrite(txd, MANTIS_I2CDATA_CTL);
			/* wait for xfer completion */
			for (trials = 0; trials < TRIALS; trials++) {
				stat = mmread(MANTIS_INT_STAT);
				if (stat & MANTIS_INT_I2CDONE)
					break;
			}

			/* check for xfer completion */
			if (stat & MANTIS_INT_I2CDONE) {
				/* check xfer was acknowledged */
				if (stat & MANTIS_INT_I2CRACK) {
					data = mmread(MANTIS_I2CDATA_CTL);
					msgs[i + 1].buf[0] = (data >> 8) & 0xff;
					dprintk(MANTIS_DEBUG, 0, "        Byte <%d> RXD=0x%02x  [%02x]\n", 0x0, data, msgs[i + 1].buf[0]);
				} else {
					/* I/O error */
					dprintk(MANTIS_ERROR, 1, "        I/O error, LINE:%d", __LINE__);
					ret = -EIO;
					break;
				}
			} else {
				/* I/O error */
				dprintk(MANTIS_ERROR, 1, "        I/O error, LINE:%d", __LINE__);
				ret = -EIO;
				break;
			}
			i += 2; /* Write/Read operation in one go */
		}

		if (i < num) {
			if (msgs[i].flags & I2C_M_RD)
				ret = mantis_i2c_read(mantis, &msgs[i]);
			else
				ret = mantis_i2c_write(mantis, &msgs[i]);

			i++;
			if (ret < 0)
				goto bail_out;
		}

	}

	mutex_unlock(&mantis->i2c_lock);

	return num;

bail_out:
	mutex_unlock(&mantis->i2c_lock);
	return ret;
}