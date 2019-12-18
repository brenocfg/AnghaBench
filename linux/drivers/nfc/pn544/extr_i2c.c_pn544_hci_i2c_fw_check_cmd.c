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
typedef  int u32 ;
typedef  int u16 ;
struct pn544_i2c_fw_frame_check {int* be_start_addr; int /*<<< orphan*/  be_crc; int /*<<< orphan*/  be_datalen; int /*<<< orphan*/  be_length; int /*<<< orphan*/  cmd; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PN544_FW_CMD_CHECK ; 
 int crc_ccitt (int,int /*<<< orphan*/  const*,int) ; 
 int i2c_master_send (struct i2c_client*,char const*,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pn544_hci_i2c_fw_check_cmd(struct i2c_client *client, u32 start_addr,
				      const u8 *data, u16 datalen)
{
	struct pn544_i2c_fw_frame_check frame;
	int r;
	u16 crc;

	/* calculate local crc for the data we want to check */
	crc = crc_ccitt(0xffff, data, datalen);

	frame.cmd = PN544_FW_CMD_CHECK;

	put_unaligned_be16(sizeof(frame.be_start_addr) +
			   sizeof(frame.be_datalen) + sizeof(frame.be_crc),
			   &frame.be_length);

	/* tell the chip the memory region to which our crc applies */
	frame.be_start_addr[0] = (start_addr & 0xff0000) >> 16;
	frame.be_start_addr[1] = (start_addr & 0xff00) >> 8;
	frame.be_start_addr[2] = start_addr & 0xff;

	put_unaligned_be16(datalen, &frame.be_datalen);

	/*
	 * and give our local crc. Chip will calculate its own crc for the
	 * region and compare with ours.
	 */
	put_unaligned_be16(crc, &frame.be_crc);

	r = i2c_master_send(client, (const char *) &frame, sizeof(frame));

	if (r == sizeof(frame))
		return 0;
	else if (r < 0)
		return r;
	else
		return -EIO;
}