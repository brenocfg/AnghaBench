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
typedef  int u16 ;
typedef  int /*<<< orphan*/  tx_data ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DW9807_CTRL_DELAY_US ; 
 int DW9807_MSB_ADDR ; 
 int EBUSY ; 
 int MAX_RETRY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dw9807_i2c_check ; 
 int i2c_master_send (struct i2c_client*,char const*,int) ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct i2c_client*,int,int,int,int) ; 

__attribute__((used)) static int dw9807_set_dac(struct i2c_client *client, u16 data)
{
	const char tx_data[3] = {
		DW9807_MSB_ADDR, ((data >> 8) & 0x03), (data & 0xff)
	};
	int val, ret;

	/*
	 * According to the datasheet, need to check the bus status before we
	 * write VCM position. This ensure that we really write the value
	 * into the register
	 */
	ret = readx_poll_timeout(dw9807_i2c_check, client, val, val <= 0,
			DW9807_CTRL_DELAY_US, MAX_RETRY * DW9807_CTRL_DELAY_US);

	if (ret || val < 0) {
		if (ret) {
			dev_warn(&client->dev,
				"Cannot do the write operation because VCM is busy\n");
		}

		return ret ? -EBUSY : val;
	}

	/* Write VCM position to registers */
	ret = i2c_master_send(client, tx_data, sizeof(tx_data));
	if (ret < 0) {
		dev_err(&client->dev,
			"I2C write MSB fail ret=%d\n", ret);

		return ret;
	}

	return 0;
}