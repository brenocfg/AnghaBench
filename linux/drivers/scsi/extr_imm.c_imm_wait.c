#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned short base; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 int /*<<< orphan*/  DID_TIME_OUT ; 
 int IMM_SPIN_TMO ; 
 int /*<<< orphan*/  imm_fail (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 unsigned char r_str (unsigned short) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 

__attribute__((used)) static unsigned char imm_wait(imm_struct *dev)
{
	int k;
	unsigned short ppb = dev->base;
	unsigned char r;

	w_ctr(ppb, 0x0c);

	k = IMM_SPIN_TMO;
	do {
		r = r_str(ppb);
		k--;
		udelay(1);
	}
	while (!(r & 0x80) && (k));

	/*
	 * STR register (LPT base+1) to SCSI mapping:
	 *
	 * STR      imm     imm
	 * ===================================
	 * 0x80     S_REQ   S_REQ
	 * 0x40     !S_BSY  (????)
	 * 0x20     !S_CD   !S_CD
	 * 0x10     !S_IO   !S_IO
	 * 0x08     (????)  !S_BSY
	 *
	 * imm      imm     meaning
	 * ==================================
	 * 0xf0     0xb8    Bit mask
	 * 0xc0     0x88    ZIP wants more data
	 * 0xd0     0x98    ZIP wants to send more data
	 * 0xe0     0xa8    ZIP is expecting SCSI command data
	 * 0xf0     0xb8    end of transfer, ZIP is sending status
	 */
	w_ctr(ppb, 0x04);
	if (k)
		return (r & 0xb8);

	/* Counter expired - Time out occurred */
	imm_fail(dev, DID_TIME_OUT);
	printk("imm timeout in imm_wait\n");
	return 0;		/* command timed out */
}