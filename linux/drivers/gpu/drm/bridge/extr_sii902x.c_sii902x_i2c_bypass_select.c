#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sii902x {TYPE_1__* i2c; } ;
struct i2c_mux_core {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS ; 
 int /*<<< orphan*/  SII902X_SYS_CTRL_DATA ; 
 int SII902X_SYS_CTRL_DDC_BUS_GRTD ; 
 int /*<<< orphan*/  SII902X_SYS_CTRL_DDC_BUS_REQ ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sii902x* i2c_mux_priv (struct i2c_mux_core*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int sii902x_read_unlocked (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int sii902x_update_bits_unlocked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sii902x_write_unlocked (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int sii902x_i2c_bypass_select(struct i2c_mux_core *mux, u32 chan_id)
{
	struct sii902x *sii902x = i2c_mux_priv(mux);
	struct device *dev = &sii902x->i2c->dev;
	unsigned long timeout;
	u8 status;
	int ret;

	ret = sii902x_update_bits_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					   SII902X_SYS_CTRL_DDC_BUS_REQ,
					   SII902X_SYS_CTRL_DDC_BUS_REQ);
	if (ret)
		return ret;

	timeout = jiffies +
		  msecs_to_jiffies(SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS);
	do {
		ret = sii902x_read_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					    &status);
		if (ret)
			return ret;
	} while (!(status & SII902X_SYS_CTRL_DDC_BUS_GRTD) &&
		 time_before(jiffies, timeout));

	if (!(status & SII902X_SYS_CTRL_DDC_BUS_GRTD)) {
		dev_err(dev, "Failed to acquire the i2c bus\n");
		return -ETIMEDOUT;
	}

	return sii902x_write_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
				      status);
}