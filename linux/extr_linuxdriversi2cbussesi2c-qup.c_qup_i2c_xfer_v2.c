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
struct qup_i2c_dev {int use_dma; int is_last; int /*<<< orphan*/  dev; struct i2c_msg* msg; int /*<<< orphan*/  xfer; scalar_t__ base; scalar_t__ qup_err; scalar_t__ bus_err; } ;
struct i2c_msg {int flags; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int I2C_MINI_CORE ; 
 int I2C_M_RD ; 
 int I2C_N_VAL_V2 ; 
 int /*<<< orphan*/  ONE_BYTE ; 
 scalar_t__ QUP_CONFIG ; 
 scalar_t__ QUP_I2C_MASTER_GEN ; 
 int /*<<< orphan*/  QUP_RESET_STATE ; 
 scalar_t__ QUP_SW_RESET ; 
 int QUP_V2_TAGS_EN ; 
 struct qup_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int qup_i2c_bam_xfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int qup_i2c_bus_active (struct qup_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qup_i2c_change_state (struct qup_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qup_i2c_conf_mode_v2 (struct qup_i2c_dev*) ; 
 int qup_i2c_determine_mode_v2 (struct qup_i2c_dev*,struct i2c_msg*,int) ; 
 int qup_i2c_poll_state (struct qup_i2c_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ qup_i2c_poll_state_i2c_master (struct qup_i2c_dev*) ; 
 int qup_i2c_xfer_v2_msg (struct qup_i2c_dev*,int,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int qup_i2c_xfer_v2(struct i2c_adapter *adap,
			   struct i2c_msg msgs[],
			   int num)
{
	struct qup_i2c_dev *qup = i2c_get_adapdata(adap);
	int ret, idx = 0;

	qup->bus_err = 0;
	qup->qup_err = 0;

	ret = pm_runtime_get_sync(qup->dev);
	if (ret < 0)
		goto out;

	ret = qup_i2c_determine_mode_v2(qup, msgs, num);
	if (ret)
		goto out;

	writel(1, qup->base + QUP_SW_RESET);
	ret = qup_i2c_poll_state(qup, QUP_RESET_STATE);
	if (ret)
		goto out;

	/* Configure QUP as I2C mini core */
	writel(I2C_MINI_CORE | I2C_N_VAL_V2, qup->base + QUP_CONFIG);
	writel(QUP_V2_TAGS_EN, qup->base + QUP_I2C_MASTER_GEN);

	if (qup_i2c_poll_state_i2c_master(qup)) {
		ret = -EIO;
		goto out;
	}

	if (qup->use_dma) {
		reinit_completion(&qup->xfer);
		ret = qup_i2c_bam_xfer(adap, &msgs[0], num);
		qup->use_dma = false;
	} else {
		qup_i2c_conf_mode_v2(qup);

		for (idx = 0; idx < num; idx++) {
			qup->msg = &msgs[idx];
			qup->is_last = idx == (num - 1);

			ret = qup_i2c_xfer_v2_msg(qup, idx,
					!!(msgs[idx].flags & I2C_M_RD));
			if (ret)
				break;
		}
		qup->msg = NULL;
	}

	if (!ret)
		ret = qup_i2c_bus_active(qup, ONE_BYTE);

	if (!ret)
		qup_i2c_change_state(qup, QUP_RESET_STATE);

	if (ret == 0)
		ret = num;
out:
	pm_runtime_mark_last_busy(qup->dev);
	pm_runtime_put_autosuspend(qup->dev);

	return ret;
}