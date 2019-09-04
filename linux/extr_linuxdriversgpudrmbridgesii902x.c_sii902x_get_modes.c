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
typedef  int /*<<< orphan*/  u32 ;
struct sii902x {TYPE_1__* i2c; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct edid {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  display_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; struct device dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_1X24 ; 
 int /*<<< orphan*/  SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS ; 
 int /*<<< orphan*/  SII902X_SYS_CTRL_DATA ; 
 unsigned int SII902X_SYS_CTRL_DDC_BUS_GRTD ; 
 unsigned int SII902X_SYS_CTRL_DDC_BUS_REQ ; 
 struct sii902x* connector_to_sii902x (struct drm_connector*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int drm_display_info_set_bus_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int sii902x_get_modes(struct drm_connector *connector)
{
	struct sii902x *sii902x = connector_to_sii902x(connector);
	struct regmap *regmap = sii902x->regmap;
	u32 bus_format = MEDIA_BUS_FMT_RGB888_1X24;
	struct device *dev = &sii902x->i2c->dev;
	unsigned long timeout;
	unsigned int retries;
	unsigned int status;
	struct edid *edid;
	int num = 0;
	int ret;

	ret = regmap_update_bits(regmap, SII902X_SYS_CTRL_DATA,
				 SII902X_SYS_CTRL_DDC_BUS_REQ,
				 SII902X_SYS_CTRL_DDC_BUS_REQ);
	if (ret)
		return ret;

	timeout = jiffies +
		  msecs_to_jiffies(SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS);
	do {
		ret = regmap_read(regmap, SII902X_SYS_CTRL_DATA, &status);
		if (ret)
			return ret;
	} while (!(status & SII902X_SYS_CTRL_DDC_BUS_GRTD) &&
		 time_before(jiffies, timeout));

	if (!(status & SII902X_SYS_CTRL_DDC_BUS_GRTD)) {
		dev_err(dev, "failed to acquire the i2c bus\n");
		return -ETIMEDOUT;
	}

	ret = regmap_write(regmap, SII902X_SYS_CTRL_DATA, status);
	if (ret)
		return ret;

	edid = drm_get_edid(connector, sii902x->i2c->adapter);
	drm_connector_update_edid_property(connector, edid);
	if (edid) {
		num = drm_add_edid_modes(connector, edid);
		kfree(edid);
	}

	ret = drm_display_info_set_bus_formats(&connector->display_info,
					       &bus_format, 1);
	if (ret)
		return ret;

	/*
	 * Sometimes the I2C bus can stall after failure to use the
	 * EDID channel. Retry a few times to see if things clear
	 * up, else continue anyway.
	 */
	retries = 5;
	do {
		ret = regmap_read(regmap, SII902X_SYS_CTRL_DATA,
				  &status);
		retries--;
	} while (ret && retries);
	if (ret)
		dev_err(dev, "failed to read status (%d)\n", ret);

	ret = regmap_update_bits(regmap, SII902X_SYS_CTRL_DATA,
				 SII902X_SYS_CTRL_DDC_BUS_REQ |
				 SII902X_SYS_CTRL_DDC_BUS_GRTD, 0);
	if (ret)
		return ret;

	timeout = jiffies +
		  msecs_to_jiffies(SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS);
	do {
		ret = regmap_read(regmap, SII902X_SYS_CTRL_DATA, &status);
		if (ret)
			return ret;
	} while (status & (SII902X_SYS_CTRL_DDC_BUS_REQ |
			   SII902X_SYS_CTRL_DDC_BUS_GRTD) &&
		 time_before(jiffies, timeout));

	if (status & (SII902X_SYS_CTRL_DDC_BUS_REQ |
		      SII902X_SYS_CTRL_DDC_BUS_GRTD)) {
		dev_err(dev, "failed to release the i2c bus\n");
		return -ETIMEDOUT;
	}

	return num;
}