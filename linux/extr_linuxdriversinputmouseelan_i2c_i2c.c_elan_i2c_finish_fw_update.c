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
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int ETP_I2C_INF_LENGTH ; 
 int ETP_I2C_REPORT_LEN ; 
 int /*<<< orphan*/  ETP_I2C_RESET ; 
 int /*<<< orphan*/  ETP_I2C_STAND_CMD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int elan_i2c_write_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (struct completion*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elan_i2c_finish_fw_update(struct i2c_client *client,
				     struct completion *completion)
{
	struct device *dev = &client->dev;
	int error;
	int len;
	u8 buffer[ETP_I2C_REPORT_LEN];

	len = i2c_master_recv(client, buffer, ETP_I2C_REPORT_LEN);
	if (len != ETP_I2C_REPORT_LEN) {
		error = len < 0 ? len : -EIO;
		dev_warn(dev, "failed to read I2C data after FW WDT reset: %d (%d)\n",
			error, len);
	}

	reinit_completion(completion);
	enable_irq(client->irq);

	error = elan_i2c_write_cmd(client, ETP_I2C_STAND_CMD, ETP_I2C_RESET);
	if (error) {
		dev_err(dev, "device reset failed: %d\n", error);
	} else if (!wait_for_completion_timeout(completion,
						msecs_to_jiffies(300))) {
		dev_err(dev, "timeout waiting for device reset\n");
		error = -ETIMEDOUT;
	}

	disable_irq(client->irq);

	if (error)
		return error;

	len = i2c_master_recv(client, buffer, ETP_I2C_INF_LENGTH);
	if (len != ETP_I2C_INF_LENGTH) {
		error = len < 0 ? len : -EIO;
		dev_err(dev, "failed to read INT signal: %d (%d)\n",
			error, len);
		return error;
	}

	return 0;
}