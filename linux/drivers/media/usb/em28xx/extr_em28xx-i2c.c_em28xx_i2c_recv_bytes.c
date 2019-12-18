#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct em28xx {int (* em28xx_read_reg_req_len ) (struct em28xx*,int,int,int /*<<< orphan*/ *,int) ;int (* em28xx_read_reg ) (struct em28xx*,int) ;TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dprintk (int,char*,int,...) ; 
 int stub1 (struct em28xx*,int,int,int /*<<< orphan*/ *,int) ; 
 int stub2 (struct em28xx*,int) ; 

__attribute__((used)) static int em28xx_i2c_recv_bytes(struct em28xx *dev, u16 addr, u8 *buf, u16 len)
{
	int ret;

	if (len < 1 || len > 64)
		return -EOPNOTSUPP;
	/*
	 * NOTE: limited by the USB ctrl message constraints
	 * Zero length reads always succeed, even if no device is connected
	 */

	/* Read data from i2c device */
	ret = dev->em28xx_read_reg_req_len(dev, 2, addr, buf, len);
	if (ret < 0) {
		dev_warn(&dev->intf->dev,
			 "reading from i2c device at 0x%x failed (error=%i)\n",
			 addr, ret);
		return ret;
	}
	/*
	 * NOTE: some devices with two i2c buses have the bad habit to return 0
	 * bytes if we are on bus B AND there was no write attempt to the
	 * specified slave address before AND no device is present at the
	 * requested slave address.
	 * Anyway, the next check will fail with -ENXIO in this case, so avoid
	 * spamming the system log on device probing and do nothing here.
	 */

	/* Check success of the i2c operation */
	ret = dev->em28xx_read_reg(dev, 0x05);
	if (ret == 0) /* success */
		return len;
	if (ret < 0) {
		dev_warn(&dev->intf->dev,
			 "failed to get i2c transfer status from bridge register (error=%i)\n",
			 ret);
		return ret;
	}
	if (ret == 0x10) {
		dprintk(1, "I2C ACK error on writing to addr 0x%02x\n",
			addr);
		return -ENXIO;
	}

	if (ret == 0x02 || ret == 0x04) {
		/* NOTE: these errors seem to be related to clock stretching */
		dprintk(0,
			"write to i2c device at 0x%x timed out (status=%i)\n",
			addr, ret);
		return -ETIMEDOUT;
	}

	dev_warn(&dev->intf->dev,
		 "write to i2c device at 0x%x failed with unknown error (status=%i)\n",
		 addr, ret);
	return -EIO;
}