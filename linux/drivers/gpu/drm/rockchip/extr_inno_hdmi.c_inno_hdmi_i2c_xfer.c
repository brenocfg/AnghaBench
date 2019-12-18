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
struct inno_hdmi_i2c {int /*<<< orphan*/  lock; } ;
struct inno_hdmi {int /*<<< orphan*/  dev; struct inno_hdmi_i2c* i2c; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  len; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HDMI_INTERRUPT_MASK1 ; 
 int /*<<< orphan*/  HDMI_INTERRUPT_STATUS1 ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  hdmi_writeb (struct inno_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inno_hdmi* i2c_get_adapdata (struct i2c_adapter*) ; 
 int inno_hdmi_i2c_read (struct inno_hdmi*,struct i2c_msg*) ; 
 int inno_hdmi_i2c_write (struct inno_hdmi*,struct i2c_msg*) ; 
 int /*<<< orphan*/  m_INT_EDID_READY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inno_hdmi_i2c_xfer(struct i2c_adapter *adap,
			      struct i2c_msg *msgs, int num)
{
	struct inno_hdmi *hdmi = i2c_get_adapdata(adap);
	struct inno_hdmi_i2c *i2c = hdmi->i2c;
	int i, ret = 0;

	mutex_lock(&i2c->lock);

	/* Clear the EDID interrupt flag and unmute the interrupt */
	hdmi_writeb(hdmi, HDMI_INTERRUPT_MASK1, m_INT_EDID_READY);
	hdmi_writeb(hdmi, HDMI_INTERRUPT_STATUS1, m_INT_EDID_READY);

	for (i = 0; i < num; i++) {
		DRM_DEV_DEBUG(hdmi->dev,
			      "xfer: num: %d/%d, len: %d, flags: %#x\n",
			      i + 1, num, msgs[i].len, msgs[i].flags);

		if (msgs[i].flags & I2C_M_RD)
			ret = inno_hdmi_i2c_read(hdmi, &msgs[i]);
		else
			ret = inno_hdmi_i2c_write(hdmi, &msgs[i]);

		if (ret < 0)
			break;
	}

	if (!ret)
		ret = num;

	/* Mute HDMI EDID interrupt */
	hdmi_writeb(hdmi, HDMI_INTERRUPT_MASK1, 0);

	mutex_unlock(&i2c->lock);

	return ret;
}