#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned short base; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 int IMM_SELECT_TMO ; 
 int r_str (unsigned short) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 
 int /*<<< orphan*/  w_dtr (unsigned short,int) ; 

__attribute__((used)) static int imm_select(imm_struct *dev, int target)
{
	int k;
	unsigned short ppb = dev->base;

	/*
	 * Firstly we want to make sure there is nothing
	 * holding onto the SCSI bus.
	 */
	w_ctr(ppb, 0xc);

	k = IMM_SELECT_TMO;
	do {
		k--;
	} while ((r_str(ppb) & 0x08) && (k));

	if (!k)
		return 0;

	/*
	 * Now assert the SCSI ID (HOST and TARGET) on the data bus
	 */
	w_ctr(ppb, 0x4);
	w_dtr(ppb, 0x80 | (1 << target));
	udelay(1);

	/*
	 * Deassert SELIN first followed by STROBE
	 */
	w_ctr(ppb, 0xc);
	w_ctr(ppb, 0xd);

	/*
	 * ACK should drop low while SELIN is deasserted.
	 * FAULT should drop low when the SCSI device latches the bus.
	 */
	k = IMM_SELECT_TMO;
	do {
		k--;
	}
	while (!(r_str(ppb) & 0x08) && (k));

	/*
	 * Place the interface back into a sane state (status mode)
	 */
	w_ctr(ppb, 0xc);
	return (k) ? 1 : 0;
}