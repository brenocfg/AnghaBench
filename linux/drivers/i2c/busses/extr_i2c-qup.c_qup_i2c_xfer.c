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
struct qup_i2c_dev {int /*<<< orphan*/  dev; struct i2c_msg* msg; scalar_t__ base; scalar_t__ qup_err; scalar_t__ bus_err; } ;
struct i2c_msg {int flags; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int I2C_MINI_CORE ; 
 int I2C_M_RD ; 
 int I2C_N_VAL ; 
 scalar_t__ QUP_CONFIG ; 
 int /*<<< orphan*/  QUP_RESET_STATE ; 
 scalar_t__ QUP_SW_RESET ; 
 struct qup_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int qup_i2c_change_state (struct qup_i2c_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ qup_i2c_check_msg_len (struct i2c_msg*) ; 
 int qup_i2c_poll_state (struct qup_i2c_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ qup_i2c_poll_state_i2c_master (struct qup_i2c_dev*) ; 
 int qup_i2c_read_one (struct qup_i2c_dev*) ; 
 int qup_i2c_write_one (struct qup_i2c_dev*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int qup_i2c_xfer(struct i2c_adapter *adap,
			struct i2c_msg msgs[],
			int num)
{
	struct qup_i2c_dev *qup = i2c_get_adapdata(adap);
	int ret, idx;

	ret = pm_runtime_get_sync(qup->dev);
	if (ret < 0)
		goto out;

	qup->bus_err = 0;
	qup->qup_err = 0;

	writel(1, qup->base + QUP_SW_RESET);
	ret = qup_i2c_poll_state(qup, QUP_RESET_STATE);
	if (ret)
		goto out;

	/* Configure QUP as I2C mini core */
	writel(I2C_MINI_CORE | I2C_N_VAL, qup->base + QUP_CONFIG);

	for (idx = 0; idx < num; idx++) {
		if (qup_i2c_poll_state_i2c_master(qup)) {
			ret = -EIO;
			goto out;
		}

		if (qup_i2c_check_msg_len(&msgs[idx])) {
			ret = -EINVAL;
			goto out;
		}

		qup->msg = &msgs[idx];
		if (msgs[idx].flags & I2C_M_RD)
			ret = qup_i2c_read_one(qup);
		else
			ret = qup_i2c_write_one(qup);

		if (ret)
			break;

		ret = qup_i2c_change_state(qup, QUP_RESET_STATE);
		if (ret)
			break;
	}

	if (ret == 0)
		ret = num;
out:

	pm_runtime_mark_last_busy(qup->dev);
	pm_runtime_put_autosuspend(qup->dev);

	return ret;
}