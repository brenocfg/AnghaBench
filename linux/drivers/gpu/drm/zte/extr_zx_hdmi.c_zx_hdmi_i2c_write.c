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
struct zx_hdmi {int dummy; } ;
struct i2c_msg {int len; int addr; int* buf; } ;

/* Variables and functions */
 int DDC_ADDR ; 
 int DDC_SEGMENT_ADDR ; 
 int EINVAL ; 
 int /*<<< orphan*/  ZX_DDC_ADDR ; 
 int /*<<< orphan*/  ZX_DDC_OFFSET ; 
 int /*<<< orphan*/  ZX_DDC_SEGM ; 
 int /*<<< orphan*/  hdmi_writeb (struct zx_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zx_hdmi_i2c_write(struct zx_hdmi *hdmi, struct i2c_msg *msg)
{
	/*
	 * The DDC I2C adapter is only for reading EDID data, so we assume
	 * that the write to this adapter must be the EDID data offset.
	 */
	if ((msg->len != 1) ||
	    ((msg->addr != DDC_ADDR) && (msg->addr != DDC_SEGMENT_ADDR)))
		return -EINVAL;

	if (msg->addr == DDC_SEGMENT_ADDR)
		hdmi_writeb(hdmi, ZX_DDC_SEGM, msg->addr << 1);
	else if (msg->addr == DDC_ADDR)
		hdmi_writeb(hdmi, ZX_DDC_ADDR, msg->addr << 1);

	hdmi_writeb(hdmi, ZX_DDC_OFFSET, msg->buf[0]);

	return 0;
}