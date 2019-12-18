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
typedef  int /*<<< orphan*/  u32 ;
struct usbnet {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int WUF_CFGX ; 
 int WUF_MASKX ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int smsc75xx_write_reg (struct usbnet*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smsc75xx_write_wuff(struct usbnet *dev, int filter, u32 wuf_cfg,
			       u32 wuf_mask1)
{
	int cfg_base = WUF_CFGX + filter * 4;
	int mask_base = WUF_MASKX + filter * 16;
	int ret;

	ret = smsc75xx_write_reg(dev, cfg_base, wuf_cfg);
	if (ret < 0) {
		netdev_warn(dev->net, "Error writing WUF_CFGX\n");
		return ret;
	}

	ret = smsc75xx_write_reg(dev, mask_base, wuf_mask1);
	if (ret < 0) {
		netdev_warn(dev->net, "Error writing WUF_MASKX\n");
		return ret;
	}

	ret = smsc75xx_write_reg(dev, mask_base + 4, 0);
	if (ret < 0) {
		netdev_warn(dev->net, "Error writing WUF_MASKX\n");
		return ret;
	}

	ret = smsc75xx_write_reg(dev, mask_base + 8, 0);
	if (ret < 0) {
		netdev_warn(dev->net, "Error writing WUF_MASKX\n");
		return ret;
	}

	ret = smsc75xx_write_reg(dev, mask_base + 12, 0);
	if (ret < 0) {
		netdev_warn(dev->net, "Error writing WUF_MASKX\n");
		return ret;
	}

	return 0;
}