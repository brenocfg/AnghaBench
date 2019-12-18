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
struct oaktrail_hdmi_dev {struct hdmi_i2c_dev* i2c_dev; } ;
struct i2c_msg {int flags; scalar_t__ buf; scalar_t__ len; } ;
struct i2c_adapter {int dummy; } ;
struct hdmi_i2c_dev {int /*<<< orphan*/  i2c_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_ICRH ; 
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  hdmi_i2c_irq_disable (struct oaktrail_hdmi_dev*) ; 
 int /*<<< orphan*/  hdmi_i2c_irq_enable (struct oaktrail_hdmi_dev*) ; 
 struct oaktrail_hdmi_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfer_read (struct i2c_adapter*,struct i2c_msg*) ; 
 int /*<<< orphan*/  xfer_write (struct i2c_adapter*,struct i2c_msg*) ; 

__attribute__((used)) static int oaktrail_hdmi_i2c_access(struct i2c_adapter *adap,
				struct i2c_msg *pmsg,
				int num)
{
	struct oaktrail_hdmi_dev *hdmi_dev = i2c_get_adapdata(adap);
	struct hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	int i;

	mutex_lock(&i2c_dev->i2c_lock);

	/* Enable i2c unit */
	HDMI_WRITE(HDMI_ICRH, 0x00008760);

	/* Enable irq */
	hdmi_i2c_irq_enable(hdmi_dev);
	for (i = 0; i < num; i++) {
		if (pmsg->len && pmsg->buf) {
			if (pmsg->flags & I2C_M_RD)
				xfer_read(adap, pmsg);
			else
				xfer_write(adap, pmsg);
		}
		pmsg++;         /* next message */
	}

	/* Disable irq */
	hdmi_i2c_irq_disable(hdmi_dev);

	mutex_unlock(&i2c_dev->i2c_lock);

	return i;
}