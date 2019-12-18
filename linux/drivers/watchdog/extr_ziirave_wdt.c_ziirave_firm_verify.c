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
typedef  int u32 ;
typedef  int u16 ;
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct ihex_binrec {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_READ_BYTE ; 
 int ZIIRAVE_FIRM_PKT_DATA_SIZE ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int const) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct ihex_binrec* ihex_next_binrec (struct ihex_binrec const*) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int const) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 scalar_t__ ziirave_firm_addr_readonly (int const) ; 
 int ziirave_firm_set_read_addr (struct watchdog_device*,int const) ; 

__attribute__((used)) static int ziirave_firm_verify(struct watchdog_device *wdd,
			       const struct firmware *fw)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	const struct ihex_binrec *rec;
	int i, ret;
	u8 data[ZIIRAVE_FIRM_PKT_DATA_SIZE];

	for (rec = (void *)fw->data; rec; rec = ihex_next_binrec(rec)) {
		const u16 len = be16_to_cpu(rec->len);
		const u32 addr = be32_to_cpu(rec->addr);

		if (ziirave_firm_addr_readonly(addr))
			continue;

		ret = ziirave_firm_set_read_addr(wdd, addr);
		if (ret) {
			dev_err(&client->dev,
				"Failed to send SET_READ_ADDR command: %d\n",
				ret);
			return ret;
		}

		for (i = 0; i < len; i++) {
			ret = i2c_smbus_read_byte_data(client,
						ZIIRAVE_CMD_DOWNLOAD_READ_BYTE);
			if (ret < 0) {
				dev_err(&client->dev,
					"Failed to READ DATA: %d\n", ret);
				return ret;
			}
			data[i] = ret;
		}

		if (memcmp(data, rec->data, len)) {
			dev_err(&client->dev,
				"Firmware mismatch at address 0x%04x\n", addr);
			return -EINVAL;
		}
	}

	return 0;
}