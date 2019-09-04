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
struct idt_smb_seq {scalar_t__ bytecnt; int ccode; int /*<<< orphan*/  data; } ;
struct idt_89hpesx_dev {int /*<<< orphan*/  client; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int CCODE_BLOCK ; 
 int CCODE_END ; 
 int CCODE_START ; 
 int EINVAL ; 
 int ENODATA ; 
 scalar_t__ I2C_SMBUS_BLOCK_MAX ; 
 scalar_t__ idt_smb_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_block ; 

__attribute__((used)) static int idt_smb_read_block(struct idt_89hpesx_dev *pdev,
			      struct idt_smb_seq *seq)
{
	s32 sts;
	u8 ccode;

	/* Return error if too much data passed to send */
	if (seq->bytecnt > I2C_SMBUS_BLOCK_MAX)
		return -EINVAL;

	/* Collect the command code byte */
	ccode = seq->ccode | CCODE_BLOCK | CCODE_START | CCODE_END;

	/* Read block of data from the device */
	sts = idt_smb_safe(read_block, pdev->client, ccode, seq->data);
	if (sts != seq->bytecnt)
		return (sts < 0 ? sts : -ENODATA);

	return 0;
}