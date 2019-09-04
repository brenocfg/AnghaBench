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
 size_t CMD_REPORT_ID_OFFSET ; 
 int EINVAL ; 
 int PKT_WRITE_SIZE ; 
 int /*<<< orphan*/  WDT_COMMAND_DELAY_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,size_t) ; 

__attribute__((used)) static int wdt87xx_set_feature(struct i2c_client *client,
			       const u8 *buf, size_t buf_size)
{
	u8 tx_buf[PKT_WRITE_SIZE];
	int tx_len = 0;
	int error;

	/* Set feature command packet */
	tx_buf[tx_len++] = 0x22;
	tx_buf[tx_len++] = 0x00;
	if (buf[CMD_REPORT_ID_OFFSET] > 0xF) {
		tx_buf[tx_len++] = 0x30;
		tx_buf[tx_len++] = 0x03;
		tx_buf[tx_len++] = buf[CMD_REPORT_ID_OFFSET];
	} else {
		tx_buf[tx_len++] = 0x30 | buf[CMD_REPORT_ID_OFFSET];
		tx_buf[tx_len++] = 0x03;
	}
	tx_buf[tx_len++] = 0x23;
	tx_buf[tx_len++] = 0x00;
	tx_buf[tx_len++] = (buf_size & 0xFF);
	tx_buf[tx_len++] = ((buf_size & 0xFF00) >> 8);

	if (tx_len + buf_size > sizeof(tx_buf))
		return -EINVAL;

	memcpy(&tx_buf[tx_len], buf, buf_size);
	tx_len += buf_size;

	error = i2c_master_send(client, tx_buf, tx_len);
	if (error < 0) {
		dev_err(&client->dev, "set feature failed: %d\n", error);
		return error;
	}

	mdelay(WDT_COMMAND_DELAY_MS);

	return 0;
}