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
struct rc_dev {struct mceusb_dev* priv; } ;
struct mceusb_dev {int wideband_rx_enabled; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  cmdbuf ;

/* Variables and functions */
 int MCE_CMD_PORT_IR ; 
 int MCE_CMD_SETIRRXPORTEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mce_command_out (struct mceusb_dev*,unsigned char*,int) ; 

__attribute__((used)) static int mceusb_set_rx_wideband(struct rc_dev *dev, int enable)
{
	struct mceusb_dev *ir = dev->priv;
	unsigned char cmdbuf[3] = { MCE_CMD_PORT_IR,
				    MCE_CMD_SETIRRXPORTEN, 0x00 };

	dev_dbg(ir->dev, "select %s-range receive sensor",
		enable ? "short" : "long");
	if (enable) {
		ir->wideband_rx_enabled = true;
		cmdbuf[2] = 2;	/* port 2 is short range receiver */
	} else {
		ir->wideband_rx_enabled = false;
		cmdbuf[2] = 1;	/* port 1 is long range receiver */
	}
	mce_command_out(ir, cmdbuf, sizeof(cmdbuf));
	/* response from device sets ir->learning_active */

	return 0;
}