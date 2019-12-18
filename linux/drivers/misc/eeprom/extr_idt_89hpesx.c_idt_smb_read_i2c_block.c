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
struct idt_smb_seq {int bytecnt; scalar_t__ ccode; int /*<<< orphan*/  data; } ;
struct idt_89hpesx_dev {int /*<<< orphan*/  client; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ CCODE_BLOCK ; 
 scalar_t__ CCODE_END ; 
 scalar_t__ CCODE_START ; 
 int EINVAL ; 
 int ENODATA ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 scalar_t__ idt_smb_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  read_i2c_block ; 

__attribute__((used)) static int idt_smb_read_i2c_block(struct idt_89hpesx_dev *pdev,
				  struct idt_smb_seq *seq)
{
	u8 ccode, buf[I2C_SMBUS_BLOCK_MAX + 1];
	s32 sts;

	/* Return error if too much data passed to send */
	if (seq->bytecnt > I2C_SMBUS_BLOCK_MAX)
		return -EINVAL;

	/* Collect the command code byte */
	ccode = seq->ccode | CCODE_BLOCK | CCODE_START | CCODE_END;

	/* Read length and block of data from the device */
	sts = idt_smb_safe(read_i2c_block, pdev->client, ccode,
		seq->bytecnt + 1, buf);
	if (sts != seq->bytecnt + 1)
		return (sts < 0 ? sts : -ENODATA);
	if (buf[0] != seq->bytecnt)
		return -ENODATA;

	/* Copy retrieved data to the output data buffer */
	memcpy(seq->data, &buf[1], seq->bytecnt);

	return 0;
}