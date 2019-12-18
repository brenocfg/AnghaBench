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
struct rk3066_hdmi {TYPE_1__* i2c; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; } ;
struct TYPE_2__ {int stat; int /*<<< orphan*/  cmpltn; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  HDMI_DDC_READ_FIFO_ADDR ; 
 int HDMI_INTR_EDID_ERR ; 
 int HZ ; 
 int /*<<< orphan*/  hdmi_readb (struct rk3066_hdmi*,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rk3066_hdmi_i2c_read(struct rk3066_hdmi *hdmi, struct i2c_msg *msgs)
{
	int length = msgs->len;
	u8 *buf = msgs->buf;
	int ret;

	ret = wait_for_completion_timeout(&hdmi->i2c->cmpltn, HZ / 10);
	if (!ret || hdmi->i2c->stat & HDMI_INTR_EDID_ERR)
		return -EAGAIN;

	while (length--)
		*buf++ = hdmi_readb(hdmi, HDMI_DDC_READ_FIFO_ADDR);

	return 0;
}