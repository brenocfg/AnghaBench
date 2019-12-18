#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sii902x {TYPE_1__* i2c; } ;
struct i2c_mux_core {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS ; 
 int /*<<< orphan*/  SII902X_SYS_CTRL_DATA ; 
 int SII902X_SYS_CTRL_DDC_BUS_GRTD ; 
 int SII902X_SYS_CTRL_DDC_BUS_REQ ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct sii902x* i2c_mux_priv (struct i2c_mux_core*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int sii902x_read_unlocked (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int sii902x_update_bits_unlocked (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sii902x_i2c_bypass_deselect(struct i2c_mux_core *mux, u32 chan_id)
{
	struct sii902x *sii902x = i2c_mux_priv(mux);
	struct device *dev = &sii902x->i2c->dev;
	unsigned long timeout;
	unsigned int retries;
	u8 status;
	int ret;

	/*
	 * When the HDMI transmitter is in pass through mode, we need an
	 * (undocumented) additional delay between STOP and START conditions
	 * to guarantee the bus won't get stuck.
	 */
	udelay(30);

	/*
	 * Sometimes the I2C bus can stall after failure to use the
	 * EDID channel. Retry a few times to see if things clear
	 * up, else continue anyway.
	 */
	retries = 5;
	do {
		ret = sii902x_read_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					    &status);
		retries--;
	} while (ret && retries);
	if (ret) {
		dev_err(dev, "failed to read status (%d)\n", ret);
		return ret;
	}

	ret = sii902x_update_bits_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					   SII902X_SYS_CTRL_DDC_BUS_REQ |
					   SII902X_SYS_CTRL_DDC_BUS_GRTD, 0);
	if (ret)
		return ret;

	timeout = jiffies +
		  msecs_to_jiffies(SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS);
	do {
		ret = sii902x_read_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					    &status);
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

	return 0;
}