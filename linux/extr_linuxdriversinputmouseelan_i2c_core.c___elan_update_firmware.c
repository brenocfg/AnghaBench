#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct firmware {int* data; } ;
struct elan_tp_data {int fw_validpage_count; TYPE_1__* ops; int /*<<< orphan*/  fw_completion; struct i2c_client* client; } ;
struct TYPE_2__ {int (* prepare_fw_update ) (struct i2c_client*) ;int (* finish_fw_update ) (struct i2c_client*,int /*<<< orphan*/ *) ;int (* get_checksum ) (struct i2c_client*,int,int*) ;} ;

/* Variables and functions */
 int EIO ; 
 int ETP_FW_PAGE_SIZE ; 
 int ETP_IAP_START_ADDR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int elan_write_fw_block (struct elan_tp_data*,int const*,int,int) ; 
 int get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct i2c_client*) ; 
 int stub2 (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int stub3 (struct i2c_client*,int,int*) ; 

__attribute__((used)) static int __elan_update_firmware(struct elan_tp_data *data,
				  const struct firmware *fw)
{
	struct i2c_client *client = data->client;
	struct device *dev = &client->dev;
	int i, j;
	int error;
	u16 iap_start_addr;
	u16 boot_page_count;
	u16 sw_checksum = 0, fw_checksum = 0;

	error = data->ops->prepare_fw_update(client);
	if (error)
		return error;

	iap_start_addr = get_unaligned_le16(&fw->data[ETP_IAP_START_ADDR * 2]);

	boot_page_count = (iap_start_addr * 2) / ETP_FW_PAGE_SIZE;
	for (i = boot_page_count; i < data->fw_validpage_count; i++) {
		u16 checksum = 0;
		const u8 *page = &fw->data[i * ETP_FW_PAGE_SIZE];

		for (j = 0; j < ETP_FW_PAGE_SIZE; j += 2)
			checksum += ((page[j + 1] << 8) | page[j]);

		error = elan_write_fw_block(data, page, checksum, i);
		if (error) {
			dev_err(dev, "write page %d fail: %d\n", i, error);
			return error;
		}

		sw_checksum += checksum;
	}

	/* Wait WDT reset and power on reset */
	msleep(600);

	error = data->ops->finish_fw_update(client, &data->fw_completion);
	if (error)
		return error;

	error = data->ops->get_checksum(client, true, &fw_checksum);
	if (error)
		return error;

	if (sw_checksum != fw_checksum) {
		dev_err(dev, "checksum diff sw=[%04X], fw=[%04X]\n",
			sw_checksum, fw_checksum);
		return -EIO;
	}

	return 0;
}