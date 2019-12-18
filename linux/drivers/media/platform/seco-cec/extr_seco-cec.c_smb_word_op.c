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
typedef  int u16 ;

/* Variables and functions */
 int BRA_HOST_BUSY ; 
 int BRA_HSTS_ERR_MASK ; 
 int BRA_INUSE_STS ; 
 short BRA_SMB_CMD_BYTE_DATA ; 
 short BRA_SMB_CMD_WORD_DATA ; 
 short BRA_START ; 
#define  CMD_BYTE_DATA 129 
#define  CMD_WORD_DATA 128 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HCMD ; 
 int /*<<< orphan*/  HCNT ; 
 int /*<<< orphan*/  HDAT0 ; 
 int /*<<< orphan*/  HDAT1 ; 
 int /*<<< orphan*/  HSTS ; 
 unsigned int SMBTIMEOUT ; 
 int SMBUS_READ ; 
 int SMBUS_WRITE ; 
 int /*<<< orphan*/  SMB_POLL_UDELAY ; 
 int /*<<< orphan*/  XMIT_SLVA ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smb_word_op(short data_format, u16 slave_addr, u8 cmd, u16 data,
		       u8 operation, u16 *result)
{
	unsigned int count;
	short _data_format;
	int status = 0;

	switch (data_format) {
	case CMD_BYTE_DATA:
		_data_format = BRA_SMB_CMD_BYTE_DATA;
		break;
	case CMD_WORD_DATA:
		_data_format = BRA_SMB_CMD_WORD_DATA;
		break;
	default:
		return -EINVAL;
	}

	/* Active wait until ready */
	for (count = 0; count <= SMBTIMEOUT; ++count) {
		if (!(inb(HSTS) & BRA_INUSE_STS))
			break;
		udelay(SMB_POLL_UDELAY);
	}

	if (count > SMBTIMEOUT)
		/* Reset the lock instead of failing */
		outb(0xff, HSTS);

	outb(0x00, HCNT);
	outb((u8)(slave_addr & 0xfe) | operation, XMIT_SLVA);
	outb(cmd, HCMD);
	inb(HCNT);

	if (operation == SMBUS_WRITE) {
		outb((u8)data, HDAT0);
		outb((u8)(data >> 8), HDAT1);
	}

	outb(BRA_START + _data_format, HCNT);

	for (count = 0; count <= SMBTIMEOUT; count++) {
		if (!(inb(HSTS) & BRA_HOST_BUSY))
			break;
		udelay(SMB_POLL_UDELAY);
	}

	if (count > SMBTIMEOUT) {
		status = -EBUSY;
		goto err;
	}

	if (inb(HSTS) & BRA_HSTS_ERR_MASK) {
		status = -EIO;
		goto err;
	}

	if (operation == SMBUS_READ)
		*result = ((inb(HDAT0) & 0xff) + ((inb(HDAT1) & 0xff) << 8));

err:
	outb(0xff, HSTS);
	return status;
}