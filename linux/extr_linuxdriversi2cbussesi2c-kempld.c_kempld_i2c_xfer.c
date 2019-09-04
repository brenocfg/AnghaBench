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
struct kempld_i2c_data {int nmsgs; scalar_t__ state; scalar_t__ pos; struct i2c_msg* msg; struct kempld_device_data* pld; } ;
struct kempld_device_data {int dummy; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long HZ ; 
 scalar_t__ STATE_DONE ; 
 scalar_t__ STATE_ERROR ; 
 scalar_t__ STATE_INIT ; 
 struct kempld_i2c_data* i2c_get_adapdata (struct i2c_adapter*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kempld_get_mutex (struct kempld_device_data*) ; 
 int kempld_i2c_process (struct kempld_i2c_data*) ; 
 int /*<<< orphan*/  kempld_release_mutex (struct kempld_device_data*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int kempld_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
				int num)
{
	struct kempld_i2c_data *i2c = i2c_get_adapdata(adap);
	struct kempld_device_data *pld = i2c->pld;
	unsigned long timeout = jiffies + HZ;
	int ret;

	i2c->msg = msgs;
	i2c->pos = 0;
	i2c->nmsgs = num;
	i2c->state = STATE_INIT;

	/* Handle the transfer */
	while (time_before(jiffies, timeout)) {
		kempld_get_mutex(pld);
		ret = kempld_i2c_process(i2c);
		kempld_release_mutex(pld);

		if (i2c->state == STATE_DONE || i2c->state == STATE_ERROR)
			return (i2c->state == STATE_DONE) ? num : ret;

		if (ret == 0)
			timeout = jiffies + HZ;

		usleep_range(5, 15);
	}

	i2c->state = STATE_ERROR;

	return -ETIMEDOUT;
}