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
struct em28xx {int (* em28xx_write_regs ) (struct em28xx*,int,int*,int) ;int (* em28xx_read_reg ) (struct em28xx*,int) ;int (* em28xx_read_reg_req_len ) (struct em28xx*,int,int,int*,int) ;TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dprintk (int,char*,int) ; 
 unsigned long em28xx_i2c_timeout (struct em28xx*) ; 
 unsigned long jiffies ; 
 int stub1 (struct em28xx*,int,int*,int) ; 
 int stub2 (struct em28xx*,int) ; 
 int stub3 (struct em28xx*,int,int,int*,int) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int em2800_i2c_recv_bytes(struct em28xx *dev, u8 addr, u8 *buf, u16 len)
{
	unsigned long timeout = jiffies + em28xx_i2c_timeout(dev);
	u8 buf2[4];
	int ret;
	int i;

	if (len < 1 || len > 4)
		return -EOPNOTSUPP;

	/* trigger read */
	buf2[1] = 0x84 + len - 1;
	buf2[0] = addr;
	ret = dev->em28xx_write_regs(dev, 0x04, buf2, 2);
	if (ret != 2) {
		dev_warn(&dev->intf->dev,
			 "failed to trigger read from i2c address 0x%x (error=%i)\n",
			 addr, ret);
		return (ret < 0) ? ret : -EIO;
	}

	/* wait for completion */
	while (time_is_after_jiffies(timeout)) {
		ret = dev->em28xx_read_reg(dev, 0x05);
		if (ret == 0x84 + len - 1)
			break;
		if (ret == 0x94 + len - 1) {
			dprintk(1, "R05 returned 0x%02x: I2C ACK error\n",
				ret);
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
	if (ret != 0x84 + len - 1)
		dprintk(0, "read from i2c device at 0x%x timed out\n", addr);

	/* get the received message */
	ret = dev->em28xx_read_reg_req_len(dev, 0x00, 4 - len, buf2, len);
	if (ret != len) {
		dev_warn(&dev->intf->dev,
			 "reading from i2c device at 0x%x failed: couldn't get the received message from the bridge (error=%i)\n",
			 addr, ret);
		return (ret < 0) ? ret : -EIO;
	}
	for (i = 0; i < len; i++)
		buf[i] = buf2[len - 1 - i];

	return ret;
}