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
struct zd1301_demod_dev {struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct i2c_msg {int flags; int len; int addr; int* buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct zd1301_demod_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int zd1301_demod_rreg (struct zd1301_demod_dev*,int,int*) ; 
 int zd1301_demod_wreg (struct zd1301_demod_dev*,int,int) ; 

__attribute__((used)) static int zd1301_demod_i2c_master_xfer(struct i2c_adapter *adapter,
					struct i2c_msg msg[], int num)
{
	struct zd1301_demod_dev *dev = i2c_get_adapdata(adapter);
	struct platform_device *pdev = dev->pdev;
	int ret, i;
	unsigned long timeout;
	u8 u8tmp;

	#define I2C_XFER_TIMEOUT 5
	#define ZD1301_IS_I2C_XFER_WRITE_READ(_msg, _num) \
		(_num == 2 && !(_msg[0].flags & I2C_M_RD) && (_msg[1].flags & I2C_M_RD))
	#define ZD1301_IS_I2C_XFER_WRITE(_msg, _num) \
		(_num == 1 && !(_msg[0].flags & I2C_M_RD))
	#define ZD1301_IS_I2C_XFER_READ(_msg, _num) \
		(_num == 1 && (_msg[0].flags & I2C_M_RD))
	if (ZD1301_IS_I2C_XFER_WRITE_READ(msg, num)) {
		dev_dbg(&pdev->dev, "write&read msg[0].len=%u msg[1].len=%u\n",
			msg[0].len, msg[1].len);
		if (msg[0].len > 1 || msg[1].len > 8) {
			ret = -EOPNOTSUPP;
			goto err;
		}

		ret = zd1301_demod_wreg(dev, 0x6811, 0x80);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6812, 0x05);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6813, msg[1].addr << 1);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6801, msg[0].buf[0]);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6802, 0x00);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6803, 0x06);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6805, 0x00);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6804, msg[1].len);
		if (ret)
			goto err;

		/* Poll xfer ready */
		timeout = jiffies + msecs_to_jiffies(I2C_XFER_TIMEOUT);
		for (u8tmp = 1; !time_after(jiffies, timeout) && u8tmp;) {
			usleep_range(500, 800);

			ret = zd1301_demod_rreg(dev, 0x6804, &u8tmp);
			if (ret)
				goto err;
		}

		for (i = 0; i < msg[1].len; i++) {
			ret = zd1301_demod_rreg(dev, 0x0600 + i, &msg[1].buf[i]);
			if (ret)
				goto err;
		}
	} else if (ZD1301_IS_I2C_XFER_WRITE(msg, num)) {
		dev_dbg(&pdev->dev, "write msg[0].len=%u\n", msg[0].len);
		if (msg[0].len > 1 + 8) {
			ret = -EOPNOTSUPP;
			goto err;
		}

		ret = zd1301_demod_wreg(dev, 0x6811, 0x80);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6812, 0x01);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6813, msg[0].addr << 1);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6800, msg[0].buf[0]);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6802, 0x00);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6803, 0x06);
		if (ret)
			goto err;

		for (i = 0; i < msg[0].len - 1; i++) {
			ret = zd1301_demod_wreg(dev, 0x0600 + i, msg[0].buf[1 + i]);
			if (ret)
				goto err;
		}

		ret = zd1301_demod_wreg(dev, 0x6805, 0x80);
		if (ret)
			goto err;
		ret = zd1301_demod_wreg(dev, 0x6804, msg[0].len - 1);
		if (ret)
			goto err;

		/* Poll xfer ready */
		timeout = jiffies + msecs_to_jiffies(I2C_XFER_TIMEOUT);
		for (u8tmp = 1; !time_after(jiffies, timeout) && u8tmp;) {
			usleep_range(500, 800);

			ret = zd1301_demod_rreg(dev, 0x6804, &u8tmp);
			if (ret)
				goto err;
		}
	} else {
		dev_dbg(&pdev->dev, "unknown msg[0].len=%u\n", msg[0].len);
		ret = -EOPNOTSUPP;
		if (ret)
			goto err;
	}

	return num;
err:
	dev_dbg(&pdev->dev, "failed=%d\n", ret);
	return ret;
}