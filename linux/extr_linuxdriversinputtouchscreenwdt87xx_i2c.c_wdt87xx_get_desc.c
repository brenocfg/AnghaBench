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
typedef  int u8 ;
typedef  int /*<<< orphan*/  tx_buf ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WDT_COMMAND_DELAY_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int wdt87xx_i2c_xfer (struct i2c_client*,int*,int,int*,size_t) ; 

__attribute__((used)) static int wdt87xx_get_desc(struct i2c_client *client, u8 desc_idx,
			    u8 *buf, size_t len)
{
	u8 tx_buf[] = { 0x22, 0x00, 0x10, 0x0E, 0x23, 0x00 };
	int error;

	tx_buf[2] |= desc_idx & 0xF;

	error = wdt87xx_i2c_xfer(client, tx_buf, sizeof(tx_buf),
				 buf, len);
	if (error) {
		dev_err(&client->dev, "get desc failed: %d\n", error);
		return error;
	}

	if (buf[0] != len) {
		dev_err(&client->dev, "unexpected response to get desc: %d\n",
			buf[0]);
		return -EINVAL;
	}

	mdelay(WDT_COMMAND_DELAY_MS);

	return 0;
}