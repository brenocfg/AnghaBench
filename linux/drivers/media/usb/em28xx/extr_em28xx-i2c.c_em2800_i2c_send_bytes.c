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
typedef  int u8 ;
typedef  int u16 ;
struct em28xx {int (* em28xx_write_regs ) (struct em28xx*,int,int*,int) ;int (* em28xx_read_reg ) (struct em28xx*,int) ;TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dprintk (int,char*,int) ; 
 unsigned long em28xx_i2c_timeout (struct em28xx*) ; 
 unsigned long jiffies ; 
 int stub1 (struct em28xx*,int,int*,int) ; 
 int stub2 (struct em28xx*,int) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int em2800_i2c_send_bytes(struct em28xx *dev, u8 addr, u8 *buf, u16 len)
{
	unsigned long timeout = jiffies + em28xx_i2c_timeout(dev);
	int ret;
	u8 b2[6];

	if (len < 1 || len > 4)
		return -EOPNOTSUPP;

	b2[5] = 0x80 + len - 1;
	b2[4] = addr;
	b2[3] = buf[0];
	if (len > 1)
		b2[2] = buf[1];
	if (len > 2)
		b2[1] = buf[2];
	if (len > 3)
		b2[0] = buf[3];

	/* trigger write */
	ret = dev->em28xx_write_regs(dev, 4 - len, &b2[4 - len], 2 + len);
	if (ret != 2 + len) {
		dev_warn(&dev->intf->dev,
			 "failed to trigger write to i2c address 0x%x (error=%i)\n",
			    addr, ret);
		return (ret < 0) ? ret : -EIO;
	}
	/* wait for completion */
	while (time_is_after_jiffies(timeout)) {
		ret = dev->em28xx_read_reg(dev, 0x05);
		if (ret == 0x80 + len - 1)
			return len;
		if (ret == 0x94 + len - 1) {
			dprintk(1, "R05 returned 0x%02x: I2C ACK error\n", ret);
			return -ENXIO;
		}
		if (ret < 0) {
			dev_warn(&dev->intf->dev,
				 "failed to get i2c transfer status from bridge register (error=%i)\n",
				ret);
			return ret;
		}
		usleep_range(5000, 6000);
	}
	dprintk(0, "write to i2c device at 0x%x timed out\n", addr);
	return -ETIMEDOUT;
}