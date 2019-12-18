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
struct solo_dev {int i2c_id; int i2c_msg_num; scalar_t__ i2c_state; int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  i2c_wait; scalar_t__ i2c_msg_ptr; struct i2c_msg* i2c_msg; struct i2c_adapter* i2c_adap; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {struct solo_dev* algo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int HZ ; 
 scalar_t__ IIC_STATE_IDLE ; 
 scalar_t__ IIC_STATE_STOP ; 
 int SOLO_I2C_ADAPTERS ; 
 int /*<<< orphan*/  SOLO_IIC_CTRL ; 
 int /*<<< orphan*/  SOLO_IRQ_IIC ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long schedule_timeout (unsigned long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_i2c_start (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_irq_on (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int solo_i2c_master_xfer(struct i2c_adapter *adap,
				struct i2c_msg msgs[], int num)
{
	struct solo_dev *solo_dev = adap->algo_data;
	unsigned long timeout;
	int ret;
	int i;
	DEFINE_WAIT(wait);

	for (i = 0; i < SOLO_I2C_ADAPTERS; i++) {
		if (&solo_dev->i2c_adap[i] == adap)
			break;
	}

	if (i == SOLO_I2C_ADAPTERS)
		return num; /* XXX Right return value for failure? */

	mutex_lock(&solo_dev->i2c_mutex);
	solo_dev->i2c_id = i;
	solo_dev->i2c_msg = msgs;
	solo_dev->i2c_msg_num = num;
	solo_dev->i2c_msg_ptr = 0;

	solo_reg_write(solo_dev, SOLO_IIC_CTRL, 0);
	solo_irq_on(solo_dev, SOLO_IRQ_IIC);
	solo_i2c_start(solo_dev);

	timeout = HZ / 2;

	for (;;) {
		prepare_to_wait(&solo_dev->i2c_wait, &wait,
				TASK_INTERRUPTIBLE);

		if (solo_dev->i2c_state == IIC_STATE_STOP)
			break;

		timeout = schedule_timeout(timeout);
		if (!timeout)
			break;

		if (signal_pending(current))
			break;
	}

	finish_wait(&solo_dev->i2c_wait, &wait);
	ret = num - solo_dev->i2c_msg_num;
	solo_dev->i2c_state = IIC_STATE_IDLE;
	solo_dev->i2c_id = -1;

	mutex_unlock(&solo_dev->i2c_mutex);

	return ret;
}