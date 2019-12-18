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
struct em28xx {int (* em28xx_write_regs_req ) (struct em28xx*,int,int,int /*<<< orphan*/ *,int) ;int (* em28xx_read_reg_req ) (struct em28xx*,int,int) ;TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int,...) ; 
 int /*<<< orphan*/  dprintk (int,char*,int) ; 
 int stub1 (struct em28xx*,int,int,int /*<<< orphan*/ *,int) ; 
 int stub2 (struct em28xx*,int,int) ; 

__attribute__((used)) static int em25xx_bus_B_send_bytes(struct em28xx *dev, u16 addr, u8 *buf,
				   u16 len)
{
	int ret;

	if (len < 1 || len > 64)
		return -EOPNOTSUPP;
	/*
	 * NOTE: limited by the USB ctrl message constraints
	 * Zero length reads always succeed, even if no device is connected
	 */

	/* Set register and write value */
	ret = dev->em28xx_write_regs_req(dev, 0x06, addr, buf, len);
	if (ret != len) {
		if (ret < 0) {
			dev_warn(&dev->intf->dev,
				 "writing to i2c device at 0x%x failed (error=%i)\n",
				 addr, ret);
			return ret;
		}

		dev_warn(&dev->intf->dev,
			 "%i bytes write to i2c device at 0x%x requested, but %i bytes written\n",
			 len, addr, ret);
		return -EIO;
	}
	/* Check success */
	ret = dev->em28xx_read_reg_req(dev, 0x08, 0x0000);
	/*
	 * NOTE: the only error we've seen so far is
	 * 0x01 when the slave device is not present
	 */
	if (!ret)
		return len;

	if (ret > 0) {
		dprintk(1, "Bus B R08 returned 0x%02x: I2C ACK error\n", ret);
		return -ENXIO;
	}

	return ret;
	/*
	 * NOTE: With chip types (other chip IDs) which actually don't support
	 * this operation, it seems to succeed ALWAYS ! (even if there is no
	 * slave device or even no second i2c bus provided)
	 */
}