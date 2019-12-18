#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned short base; int mode; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
#define  IMM_EPP_16 132 
#define  IMM_EPP_32 131 
#define  IMM_EPP_8 130 
#define  IMM_NIBBLE 129 
#define  IMM_PS2 128 
 int /*<<< orphan*/  ecp_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  epp_reset (unsigned short) ; 
 int imm_byte_out (unsigned short,char*,int) ; 
 int /*<<< orphan*/  imm_fail (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int imm_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  outsb (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  outsl (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  outsw (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int r_str (unsigned short) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 

__attribute__((used)) static int imm_out(imm_struct *dev, char *buffer, int len)
{
	unsigned short ppb = dev->base;
	int r = imm_wait(dev);

	/*
	 * Make sure that:
	 * a) the SCSI bus is BUSY (device still listening)
	 * b) the device is listening
	 */
	if ((r & 0x18) != 0x08) {
		imm_fail(dev, DID_ERROR);
		printk("IMM: returned SCSI status %2x\n", r);
		return 0;
	}
	switch (dev->mode) {
	case IMM_EPP_32:
	case IMM_EPP_16:
	case IMM_EPP_8:
		epp_reset(ppb);
		w_ctr(ppb, 0x4);
#ifdef CONFIG_SCSI_IZIP_EPP16
		if (!(((long) buffer | len) & 0x01))
			outsw(ppb + 4, buffer, len >> 1);
#else
		if (!(((long) buffer | len) & 0x03))
			outsl(ppb + 4, buffer, len >> 2);
#endif
		else
			outsb(ppb + 4, buffer, len);
		w_ctr(ppb, 0xc);
		r = !(r_str(ppb) & 0x01);
		w_ctr(ppb, 0xc);
		ecp_sync(dev);
		break;

	case IMM_NIBBLE:
	case IMM_PS2:
		/* 8 bit output, with a loop */
		r = imm_byte_out(ppb, buffer, len);
		break;

	default:
		printk("IMM: bug in imm_out()\n");
		r = 0;
	}
	return r;
}