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
struct idt_smb_seq {int bytecnt; int ccode; int* data; } ;
struct idt_89hpesx_dev {int /*<<< orphan*/  client; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int CCODE_BYTE ; 
 int CCODE_END ; 
 int CCODE_START ; 
 scalar_t__ idt_smb_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_byte ; 

__attribute__((used)) static int idt_smb_read_byte(struct idt_89hpesx_dev *pdev,
			     struct idt_smb_seq *seq)
{
	s32 sts;
	u8 ccode;
	int idx;

	/* Loop over the supplied buffer receiving byte one-by-one */
	for (idx = 0; idx < seq->bytecnt; idx++) {
		/* Collect the command code byte */
		ccode = seq->ccode | CCODE_BYTE;
		if (idx == 0)
			ccode |= CCODE_START;
		if (idx == seq->bytecnt - 1)
			ccode |= CCODE_END;

		/* Read data from the device */
		sts = idt_smb_safe(read_byte, pdev->client, ccode);
		if (sts < 0)
			return (int)sts;

		seq->data[idx] = (u8)sts;
	}

	return 0;
}