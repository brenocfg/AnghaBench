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
struct pca954x {scalar_t__ last_chan; int /*<<< orphan*/  idle_state; TYPE_1__* chip; } ;
struct i2c_mux_core {int /*<<< orphan*/  parent; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int nchans; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I2C_LOCK_SEGMENT ; 
 int MUX_IDLE_AS_IS ; 
 int MUX_IDLE_DISCONNECT ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 struct i2c_mux_core* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_lock_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pca954x* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_unlock_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int pca954x_deselect_mux (struct i2c_mux_core*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t idle_state_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct i2c_mux_core *muxc = i2c_get_clientdata(client);
	struct pca954x *data = i2c_mux_priv(muxc);
	int val;
	int ret;

	ret = kstrtoint(buf, 0, &val);
	if (ret < 0)
		return ret;

	if (val != MUX_IDLE_AS_IS && val != MUX_IDLE_DISCONNECT &&
	    (val < 0 || val >= data->chip->nchans))
		return -EINVAL;

	i2c_lock_bus(muxc->parent, I2C_LOCK_SEGMENT);

	WRITE_ONCE(data->idle_state, val);
	/*
	 * Set the mux into a state consistent with the new
	 * idle_state.
	 */
	if (data->last_chan || val != MUX_IDLE_DISCONNECT)
		ret = pca954x_deselect_mux(muxc, 0);

	i2c_unlock_bus(muxc->parent, I2C_LOCK_SEGMENT);

	return ret < 0 ? ret : count;
}