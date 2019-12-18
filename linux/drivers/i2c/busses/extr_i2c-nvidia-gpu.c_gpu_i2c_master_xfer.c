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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_msg {int flags; int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct gpu_i2c_dev {int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ I2C_MST_ADDR ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gpu_i2c_read (struct gpu_i2c_dev*,int /*<<< orphan*/ *,int) ; 
 int gpu_i2c_start (struct gpu_i2c_dev*) ; 
 int gpu_i2c_stop (struct gpu_i2c_dev*) ; 
 int gpu_i2c_write (struct gpu_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 struct gpu_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int gpu_i2c_master_xfer(struct i2c_adapter *adap,
			       struct i2c_msg *msgs, int num)
{
	struct gpu_i2c_dev *i2cd = i2c_get_adapdata(adap);
	int status, status2;
	bool send_stop = true;
	int i, j;

	/*
	 * The controller supports maximum 4 byte read due to known
	 * limitation of sending STOP after every read.
	 */
	pm_runtime_get_sync(i2cd->dev);
	for (i = 0; i < num; i++) {
		if (msgs[i].flags & I2C_M_RD) {
			/* program client address before starting read */
			writel(msgs[i].addr, i2cd->regs + I2C_MST_ADDR);
			/* gpu_i2c_read has implicit start */
			status = gpu_i2c_read(i2cd, msgs[i].buf, msgs[i].len);
			if (status < 0)
				goto exit;
		} else {
			u8 addr = i2c_8bit_addr_from_msg(msgs + i);

			status = gpu_i2c_start(i2cd);
			if (status < 0) {
				if (i == 0)
					send_stop = false;
				goto exit;
			}

			status = gpu_i2c_write(i2cd, addr);
			if (status < 0)
				goto exit;

			for (j = 0; j < msgs[i].len; j++) {
				status = gpu_i2c_write(i2cd, msgs[i].buf[j]);
				if (status < 0)
					goto exit;
			}
		}
	}
	send_stop = false;
	status = gpu_i2c_stop(i2cd);
	if (status < 0)
		goto exit;

	status = i;
exit:
	if (send_stop) {
		status2 = gpu_i2c_stop(i2cd);
		if (status2 < 0)
			dev_err(i2cd->dev, "i2c stop failed %d\n", status2);
	}
	pm_runtime_mark_last_busy(i2cd->dev);
	pm_runtime_put_autosuspend(i2cd->dev);
	return status;
}