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
struct stm32f7_i2c_msg {int smbus; int result; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct stm32f7_i2c_dev {int msg_num; int /*<<< orphan*/  dev; scalar_t__ use_dma; struct i2c_msg* msg; TYPE_1__ adap; int /*<<< orphan*/  complete; scalar_t__ msg_id; struct stm32_i2c_dma* dma; struct stm32f7_i2c_msg f7_msg; } ;
struct stm32_i2c_dma {int /*<<< orphan*/  chan_using; } ;
struct i2c_msg {int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct stm32f7_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int stm32f7_i2c_wait_free_bus (struct stm32f7_i2c_dev*) ; 
 int /*<<< orphan*/  stm32f7_i2c_xfer_msg (struct stm32f7_i2c_dev*,struct i2c_msg*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32f7_i2c_xfer(struct i2c_adapter *i2c_adap,
			    struct i2c_msg msgs[], int num)
{
	struct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	struct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	struct stm32_i2c_dma *dma = i2c_dev->dma;
	unsigned long time_left;
	int ret;

	i2c_dev->msg = msgs;
	i2c_dev->msg_num = num;
	i2c_dev->msg_id = 0;
	f7_msg->smbus = false;

	ret = pm_runtime_get_sync(i2c_dev->dev);
	if (ret < 0)
		return ret;

	ret = stm32f7_i2c_wait_free_bus(i2c_dev);
	if (ret)
		goto pm_free;

	stm32f7_i2c_xfer_msg(i2c_dev, msgs);

	time_left = wait_for_completion_timeout(&i2c_dev->complete,
						i2c_dev->adap.timeout);
	ret = f7_msg->result;

	if (!time_left) {
		dev_dbg(i2c_dev->dev, "Access to slave 0x%x timed out\n",
			i2c_dev->msg->addr);
		if (i2c_dev->use_dma)
			dmaengine_terminate_all(dma->chan_using);
		ret = -ETIMEDOUT;
	}

pm_free:
	pm_runtime_mark_last_busy(i2c_dev->dev);
	pm_runtime_put_autosuspend(i2c_dev->dev);

	return (ret < 0) ? ret : num;
}