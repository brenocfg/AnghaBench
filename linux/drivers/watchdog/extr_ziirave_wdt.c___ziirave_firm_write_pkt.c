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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_PACKET ; 
 scalar_t__ ZIIRAVE_FIRM_PKT_DATA_SIZE ; 
 int ZIIRAVE_FIRM_PKT_TOTAL_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int i2c_smbus_write_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int const,scalar_t__*) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 scalar_t__ ziirave_firm_addr_readonly (scalar_t__) ; 
 int ziirave_firm_read_ack (struct watchdog_device*) ; 

__attribute__((used)) static int __ziirave_firm_write_pkt(struct watchdog_device *wdd,
				    u32 addr, const u8 *data, u8 len)
{
	const u16 addr16 = (u16)addr / 2;
	struct i2c_client *client = to_i2c_client(wdd->parent);
	u8 i, checksum = 0, packet[ZIIRAVE_FIRM_PKT_TOTAL_SIZE];
	int ret;

	/* Check max data size */
	if (len > ZIIRAVE_FIRM_PKT_DATA_SIZE) {
		dev_err(&client->dev, "Firmware packet too long (%d)\n",
			len);
		return -EMSGSIZE;
	}

	/*
	 * Ignore packets that are targeting program memory outisde of
	 * app partition, since they will be ignored by the
	 * bootloader. At the same time, we need to make sure we'll
	 * allow zero length packet that will be sent as the last step
	 * of firmware update
	 */
	if (len && ziirave_firm_addr_readonly(addr))
		return 0;

	/* Packet length */
	packet[0] = len;
	/* Packet address */
	put_unaligned_le16(addr16, packet + 1);

	memcpy(packet + 3, data, len);
	memset(packet + 3 + len, 0, ZIIRAVE_FIRM_PKT_DATA_SIZE - len);

	/* Packet checksum */
	for (i = 0; i < len + 3; i++)
		checksum += packet[i];
	packet[ZIIRAVE_FIRM_PKT_TOTAL_SIZE - 1] = checksum;

	ret = i2c_smbus_write_block_data(client, ZIIRAVE_CMD_DOWNLOAD_PACKET,
					 sizeof(packet), packet);
	if (ret) {
		dev_err(&client->dev,
			"Failed to send DOWNLOAD_PACKET: %d\n", ret);
		return ret;
	}

	ret = ziirave_firm_read_ack(wdd);
	if (ret)
		dev_err(&client->dev,
		      "Failed to write firmware packet at address 0x%04x: %d\n",
		      addr, ret);

	return ret;
}