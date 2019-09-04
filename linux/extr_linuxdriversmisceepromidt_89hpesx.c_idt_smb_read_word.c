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
typedef  scalar_t__ u16 ;
struct idt_smb_seq {int bytecnt; int ccode; int* data; } ;
struct idt_89hpesx_dev {int /*<<< orphan*/  client; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int CCODE_BYTE ; 
 int CCODE_END ; 
 int CCODE_START ; 
 int CCODE_WORD ; 
 scalar_t__ idt_smb_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_byte ; 
 int /*<<< orphan*/  read_word ; 

__attribute__((used)) static int idt_smb_read_word(struct idt_89hpesx_dev *pdev,
			     struct idt_smb_seq *seq)
{
	s32 sts;
	u8 ccode;
	int idx, evencnt;

	/* Calculate the even count of data to send */
	evencnt = seq->bytecnt - (seq->bytecnt % 2);

	/* Loop over the supplied data reading two bytes at a time */
	for (idx = 0; idx < evencnt; idx += 2) {
		/* Collect the command code byte */
		ccode = seq->ccode | CCODE_WORD;
		if (idx == 0)
			ccode |= CCODE_START;
		if (idx == evencnt - 2)
			ccode |= CCODE_END;

		/* Read word data from the device */
		sts = idt_smb_safe(read_word, pdev->client, ccode);
		if (sts < 0)
			return (int)sts;

		*(u16 *)&seq->data[idx] = (u16)sts;
	}

	/* If there is odd number of bytes then receive just one last byte */
	if (seq->bytecnt != evencnt) {
		/* Collect the command code byte */
		ccode = seq->ccode | CCODE_BYTE | CCODE_END;
		if (idx == 0)
			ccode |= CCODE_START;

		/* Read last data byte from the device */
		sts = idt_smb_safe(read_byte, pdev->client, ccode);
		if (sts < 0)
			return (int)sts;

		seq->data[idx] = (u8)sts;
	}

	return 0;
}