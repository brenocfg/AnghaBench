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
struct zx_hdmi_i2c {int /*<<< orphan*/  lock; } ;
struct zx_hdmi {int /*<<< orphan*/  dev; struct zx_hdmi_i2c* ddc; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  len; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HW_DDC_MASTER ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  TPI_DDC_MASTER_EN ; 
 int /*<<< orphan*/  hdmi_writeb_mask (struct zx_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zx_hdmi* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zx_hdmi_i2c_read (struct zx_hdmi*,struct i2c_msg*) ; 
 int zx_hdmi_i2c_write (struct zx_hdmi*,struct i2c_msg*) ; 

__attribute__((used)) static int zx_hdmi_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			    int num)
{
	struct zx_hdmi *hdmi = i2c_get_adapdata(adap);
	struct zx_hdmi_i2c *ddc = hdmi->ddc;
	int i, ret = 0;

	mutex_lock(&ddc->lock);

	/* Enable DDC master access */
	hdmi_writeb_mask(hdmi, TPI_DDC_MASTER_EN, HW_DDC_MASTER, HW_DDC_MASTER);

	for (i = 0; i < num; i++) {
		DRM_DEV_DEBUG(hdmi->dev,
			      "xfer: num: %d/%d, len: %d, flags: %#x\n",
			      i + 1, num, msgs[i].len, msgs[i].flags);

		if (msgs[i].flags & I2C_M_RD)
			ret = zx_hdmi_i2c_read(hdmi, &msgs[i]);
		else
			ret = zx_hdmi_i2c_write(hdmi, &msgs[i]);

		if (ret < 0)
			break;
	}

	if (!ret)
		ret = num;

	/* Disable DDC master access */
	hdmi_writeb_mask(hdmi, TPI_DDC_MASTER_EN, HW_DDC_MASTER, 0);

	mutex_unlock(&ddc->lock);

	return ret;
}