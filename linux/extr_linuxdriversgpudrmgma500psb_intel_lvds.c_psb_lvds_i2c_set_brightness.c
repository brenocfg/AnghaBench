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
typedef  scalar_t__ u8 ;
struct psb_intel_i2c_chan {int /*<<< orphan*/  adapter; int /*<<< orphan*/  slave_addr; } ;
struct i2c_msg {int len; scalar_t__* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct drm_psb_private {TYPE_1__* lvds_bl; struct psb_intel_i2c_chan* lvds_i2c_bus; } ;
struct drm_device {int /*<<< orphan*/  dev; scalar_t__ dev_private; } ;
struct TYPE_2__ {scalar_t__ pol; scalar_t__ brightnesscmd; } ;

/* Variables and functions */
 scalar_t__ BLC_POLARITY_INVERSE ; 
 unsigned int BRIGHTNESS_MASK ; 
 unsigned int BRIGHTNESS_MAX_LEVEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static int psb_lvds_i2c_set_brightness(struct drm_device *dev,
					unsigned int level)
{
	struct drm_psb_private *dev_priv =
		(struct drm_psb_private *)dev->dev_private;

	struct psb_intel_i2c_chan *lvds_i2c_bus = dev_priv->lvds_i2c_bus;
	u8 out_buf[2];
	unsigned int blc_i2c_brightness;

	struct i2c_msg msgs[] = {
		{
			.addr = lvds_i2c_bus->slave_addr,
			.flags = 0,
			.len = 2,
			.buf = out_buf,
		}
	};

	blc_i2c_brightness = BRIGHTNESS_MASK & ((unsigned int)level *
			     BRIGHTNESS_MASK /
			     BRIGHTNESS_MAX_LEVEL);

	if (dev_priv->lvds_bl->pol == BLC_POLARITY_INVERSE)
		blc_i2c_brightness = BRIGHTNESS_MASK - blc_i2c_brightness;

	out_buf[0] = dev_priv->lvds_bl->brightnesscmd;
	out_buf[1] = (u8)blc_i2c_brightness;

	if (i2c_transfer(&lvds_i2c_bus->adapter, msgs, 1) == 1) {
		dev_dbg(dev->dev, "I2C set brightness.(command, value) (%d, %d)\n",
			dev_priv->lvds_bl->brightnesscmd,
			blc_i2c_brightness);
		return 0;
	}

	dev_err(dev->dev, "I2C transfer error\n");
	return -1;
}