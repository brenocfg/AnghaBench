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
typedef  int u16 ;
struct pn544_i2c_phy {int /*<<< orphan*/  i2c_dev; } ;
struct pn544_i2c_fw_secure_frame {int /*<<< orphan*/  data; int /*<<< orphan*/  be_datalen; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PN544_FW_CMD_SECURE_CHUNK_WRITE ; 
 int PN544_FW_I2C_MAX_PAYLOAD ; 
 int PN544_FW_SECURE_CHUNK_WRITE_DATA_MAX_LEN ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pn544_hci_i2c_fw_secure_write_frame_cmd(struct pn544_i2c_phy *phy,
					const u8 *data, u16 datalen)
{
	u8 buf[PN544_FW_I2C_MAX_PAYLOAD];
	struct pn544_i2c_fw_secure_frame *chunk;
	int chunklen;
	int r;

	if (datalen > PN544_FW_SECURE_CHUNK_WRITE_DATA_MAX_LEN)
		datalen = PN544_FW_SECURE_CHUNK_WRITE_DATA_MAX_LEN;

	chunk = (struct pn544_i2c_fw_secure_frame *) buf;

	chunk->cmd = PN544_FW_CMD_SECURE_CHUNK_WRITE;

	put_unaligned_be16(datalen, &chunk->be_datalen);

	memcpy(chunk->data, data, datalen);

	chunklen = sizeof(chunk->cmd) + sizeof(chunk->be_datalen) + datalen;

	r = i2c_master_send(phy->i2c_dev, buf, chunklen);

	if (r == chunklen)
		return datalen;
	else if (r < 0)
		return r;
	else
		return -EIO;

}