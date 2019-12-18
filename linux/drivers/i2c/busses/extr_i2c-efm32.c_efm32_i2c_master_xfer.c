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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct efm32_i2c_ddata {int num_msgs; int current_msg; int retval; int /*<<< orphan*/  done; TYPE_1__ adapter; scalar_t__ current_word; struct i2c_msg* msgs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  REG_STATE ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_i2c_read32 (struct efm32_i2c_ddata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_i2c_send_next_msg (struct efm32_i2c_ddata*) ; 
 struct efm32_i2c_ddata* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efm32_i2c_master_xfer(struct i2c_adapter *adap,
		struct i2c_msg *msgs, int num)
{
	struct efm32_i2c_ddata *ddata = i2c_get_adapdata(adap);
	int ret;

	if (ddata->msgs)
		return -EBUSY;

	ddata->msgs = msgs;
	ddata->num_msgs = num;
	ddata->current_word = 0;
	ddata->current_msg = 0;
	ddata->retval = -EIO;

	reinit_completion(&ddata->done);

	dev_dbg(&ddata->adapter.dev, "state: %08x, status: %08x\n",
			efm32_i2c_read32(ddata, REG_STATE),
			efm32_i2c_read32(ddata, REG_STATUS));

	efm32_i2c_send_next_msg(ddata);

	wait_for_completion(&ddata->done);

	if (ddata->current_msg >= ddata->num_msgs)
		ret = ddata->num_msgs;
	else
		ret = ddata->retval;

	return ret;
}