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
struct i2c_msg {scalar_t__ flags; int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct flexcop_i2c_adapter {TYPE_1__* fc; } ;
struct TYPE_2__ {int (* i2c_request ) (struct flexcop_i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  i2c_mutex; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FC_READ ; 
 int /*<<< orphan*/  FC_WRITE ; 
 scalar_t__ I2C_M_RD ; 
 int /*<<< orphan*/  deb_i2c (char*) ; 
 struct flexcop_i2c_adapter* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct flexcop_i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int stub2 (struct flexcop_i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int flexcop_master_xfer(struct i2c_adapter *i2c_adap,
		struct i2c_msg msgs[], int num)
{
	struct flexcop_i2c_adapter *i2c = i2c_get_adapdata(i2c_adap);
	int i, ret = 0;

	/* Some drivers use 1 byte or 0 byte reads as probes, which this
	 * driver doesn't support.  These probes will always fail, so this
	 * hack makes them always succeed.  If one knew how, it would of
	 * course be better to actually do the read.  */
	if (num == 1 && msgs[0].flags == I2C_M_RD && msgs[0].len <= 1)
		return 1;

	if (mutex_lock_interruptible(&i2c->fc->i2c_mutex))
		return -ERESTARTSYS;

	for (i = 0; i < num; i++) {
		/* reading */
		if (i+1 < num && (msgs[i+1].flags == I2C_M_RD)) {
			ret = i2c->fc->i2c_request(i2c, FC_READ, msgs[i].addr,
					msgs[i].buf[0], msgs[i+1].buf,
					msgs[i+1].len);
			i++; /* skip the following message */
		} else /* writing */
			ret = i2c->fc->i2c_request(i2c, FC_WRITE, msgs[i].addr,
					msgs[i].buf[0], &msgs[i].buf[1],
					msgs[i].len - 1);
		if (ret < 0) {
			deb_i2c("i2c master_xfer failed");
			break;
		}
	}

	mutex_unlock(&i2c->fc->i2c_mutex);

	if (ret == 0)
		ret = num;
	return ret;
}