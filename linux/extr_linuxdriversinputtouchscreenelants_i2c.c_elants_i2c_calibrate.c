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
typedef  int /*<<< orphan*/  w_flashkey ;
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct elants_data {int /*<<< orphan*/  cmd_resp; int /*<<< orphan*/  state; int /*<<< orphan*/  cmd_done; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  rek_resp ;
typedef  int /*<<< orphan*/  rek ;

/* Variables and functions */
#define  CMD_HEADER_REK 128 
 int EINVAL ; 
 int /*<<< orphan*/  ELAN_CALI_TIMEOUT_MSEC ; 
 int /*<<< orphan*/  ELAN_STATE_NORMAL ; 
 int /*<<< orphan*/  ELAN_WAIT_RECALIBRATION ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elants_i2c_send (struct i2c_client*,int const*,int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elants_i2c_calibrate(struct elants_data *ts)
{
	struct i2c_client *client = ts->client;
	int ret, error;
	static const u8 w_flashkey[] = { 0x54, 0xC0, 0xE1, 0x5A };
	static const u8 rek[] = { 0x54, 0x29, 0x00, 0x01 };
	static const u8 rek_resp[] = { CMD_HEADER_REK, 0x66, 0x66, 0x66 };

	disable_irq(client->irq);

	ts->state = ELAN_WAIT_RECALIBRATION;
	reinit_completion(&ts->cmd_done);

	elants_i2c_send(client, w_flashkey, sizeof(w_flashkey));
	elants_i2c_send(client, rek, sizeof(rek));

	enable_irq(client->irq);

	ret = wait_for_completion_interruptible_timeout(&ts->cmd_done,
				msecs_to_jiffies(ELAN_CALI_TIMEOUT_MSEC));

	ts->state = ELAN_STATE_NORMAL;

	if (ret <= 0) {
		error = ret < 0 ? ret : -ETIMEDOUT;
		dev_err(&client->dev,
			"error while waiting for calibration to complete: %d\n",
			error);
		return error;
	}

	if (memcmp(rek_resp, ts->cmd_resp, sizeof(rek_resp))) {
		dev_err(&client->dev,
			"unexpected calibration response: %*ph\n",
			(int)sizeof(ts->cmd_resp), ts->cmd_resp);
		return -EINVAL;
	}

	return 0;
}