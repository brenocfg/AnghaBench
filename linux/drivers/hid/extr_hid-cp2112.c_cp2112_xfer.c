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
union i2c_smbus_data {int byte; size_t* block; int /*<<< orphan*/  word; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {scalar_t__ algo_data; } ;
struct hid_device {int dummy; } ;
struct cp2112_device {struct hid_device* hdev; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int CP2112_CANCEL_TRANSFER ; 
 int EBUSY ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
#define  I2C_SMBUS_BLOCK_DATA 134 
 size_t I2C_SMBUS_BLOCK_MAX ; 
#define  I2C_SMBUS_BLOCK_PROC_CALL 133 
#define  I2C_SMBUS_BYTE 132 
#define  I2C_SMBUS_BYTE_DATA 131 
#define  I2C_SMBUS_I2C_BLOCK_DATA 130 
#define  I2C_SMBUS_PROC_CALL 129 
 char I2C_SMBUS_READ ; 
#define  I2C_SMBUS_WORD_DATA 128 
 char I2C_SMBUS_WRITE ; 
 int /*<<< orphan*/  PM_HINT_FULLON ; 
 int /*<<< orphan*/  PM_HINT_NORMAL ; 
 unsigned int XFER_STATUS_RETRIES ; 
 int cp2112_hid_output (struct hid_device*,int*,int,int /*<<< orphan*/ ) ; 
 int cp2112_read (struct cp2112_device*,int*,size_t) ; 
 scalar_t__ cp2112_read_req (int*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ cp2112_write_read_req (int*,int /*<<< orphan*/ ,size_t,int,int*,int) ; 
 scalar_t__ cp2112_write_req (int*,int /*<<< orphan*/ ,int,int*,int) ; 
 int cp2112_xfer_status (struct cp2112_device*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,...) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 int hid_hw_power (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,...) ; 
 int /*<<< orphan*/  le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 

__attribute__((used)) static int cp2112_xfer(struct i2c_adapter *adap, u16 addr,
		       unsigned short flags, char read_write, u8 command,
		       int size, union i2c_smbus_data *data)
{
	struct cp2112_device *dev = (struct cp2112_device *)adap->algo_data;
	struct hid_device *hdev = dev->hdev;
	u8 buf[64];
	__le16 word;
	ssize_t count;
	size_t read_length = 0;
	unsigned int retries;
	int ret;

	hid_dbg(hdev, "%s addr 0x%x flags 0x%x cmd 0x%x size %d\n",
		read_write == I2C_SMBUS_WRITE ? "write" : "read",
		addr, flags, command, size);

	switch (size) {
	case I2C_SMBUS_BYTE:
		read_length = 1;

		if (I2C_SMBUS_READ == read_write)
			count = cp2112_read_req(buf, addr, read_length);
		else
			count = cp2112_write_req(buf, addr, command, NULL,
						 0);
		break;
	case I2C_SMBUS_BYTE_DATA:
		read_length = 1;

		if (I2C_SMBUS_READ == read_write)
			count = cp2112_write_read_req(buf, addr, read_length,
						      command, NULL, 0);
		else
			count = cp2112_write_req(buf, addr, command,
						 &data->byte, 1);
		break;
	case I2C_SMBUS_WORD_DATA:
		read_length = 2;
		word = cpu_to_le16(data->word);

		if (I2C_SMBUS_READ == read_write)
			count = cp2112_write_read_req(buf, addr, read_length,
						      command, NULL, 0);
		else
			count = cp2112_write_req(buf, addr, command,
						 (u8 *)&word, 2);
		break;
	case I2C_SMBUS_PROC_CALL:
		size = I2C_SMBUS_WORD_DATA;
		read_write = I2C_SMBUS_READ;
		read_length = 2;
		word = cpu_to_le16(data->word);

		count = cp2112_write_read_req(buf, addr, read_length, command,
					      (u8 *)&word, 2);
		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		if (read_write == I2C_SMBUS_READ) {
			read_length = data->block[0];
			count = cp2112_write_read_req(buf, addr, read_length,
						      command, NULL, 0);
		} else {
			count = cp2112_write_req(buf, addr, command,
						 data->block + 1,
						 data->block[0]);
		}
		break;
	case I2C_SMBUS_BLOCK_DATA:
		if (I2C_SMBUS_READ == read_write) {
			count = cp2112_write_read_req(buf, addr,
						      I2C_SMBUS_BLOCK_MAX,
						      command, NULL, 0);
		} else {
			count = cp2112_write_req(buf, addr, command,
						 data->block,
						 data->block[0] + 1);
		}
		break;
	case I2C_SMBUS_BLOCK_PROC_CALL:
		size = I2C_SMBUS_BLOCK_DATA;
		read_write = I2C_SMBUS_READ;

		count = cp2112_write_read_req(buf, addr, I2C_SMBUS_BLOCK_MAX,
					      command, data->block,
					      data->block[0] + 1);
		break;
	default:
		hid_warn(hdev, "Unsupported transaction %d\n", size);
		return -EOPNOTSUPP;
	}

	if (count < 0)
		return count;

	ret = hid_hw_power(hdev, PM_HINT_FULLON);
	if (ret < 0) {
		hid_err(hdev, "power management error: %d\n", ret);
		return ret;
	}

	ret = cp2112_hid_output(hdev, buf, count, HID_OUTPUT_REPORT);
	if (ret < 0) {
		hid_warn(hdev, "Error starting transaction: %d\n", ret);
		goto power_normal;
	}

	for (retries = 0; retries < XFER_STATUS_RETRIES; ++retries) {
		ret = cp2112_xfer_status(dev);
		if (-EBUSY == ret)
			continue;
		if (ret < 0)
			goto power_normal;
		break;
	}

	if (XFER_STATUS_RETRIES <= retries) {
		hid_warn(hdev, "Transfer timed out, cancelling.\n");
		buf[0] = CP2112_CANCEL_TRANSFER;
		buf[1] = 0x01;

		ret = cp2112_hid_output(hdev, buf, 2, HID_OUTPUT_REPORT);
		if (ret < 0)
			hid_warn(hdev, "Error cancelling transaction: %d\n",
				 ret);

		ret = -ETIMEDOUT;
		goto power_normal;
	}

	if (I2C_SMBUS_WRITE == read_write) {
		ret = 0;
		goto power_normal;
	}

	if (I2C_SMBUS_BLOCK_DATA == size)
		read_length = ret;

	ret = cp2112_read(dev, buf, read_length);
	if (ret < 0)
		goto power_normal;
	if (ret != read_length) {
		hid_warn(hdev, "short read: %d < %zd\n", ret, read_length);
		ret = -EIO;
		goto power_normal;
	}

	switch (size) {
	case I2C_SMBUS_BYTE:
	case I2C_SMBUS_BYTE_DATA:
		data->byte = buf[0];
		break;
	case I2C_SMBUS_WORD_DATA:
		data->word = le16_to_cpup((__le16 *)buf);
		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		memcpy(data->block + 1, buf, read_length);
		break;
	case I2C_SMBUS_BLOCK_DATA:
		if (read_length > I2C_SMBUS_BLOCK_MAX) {
			ret = -EPROTO;
			goto power_normal;
		}

		memcpy(data->block, buf, read_length);
		break;
	}

	ret = 0;
power_normal:
	hid_hw_power(hdev, PM_HINT_NORMAL);
	hid_dbg(hdev, "transfer finished: %d\n", ret);
	return ret;
}