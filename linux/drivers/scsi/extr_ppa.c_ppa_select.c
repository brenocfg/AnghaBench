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
typedef  TYPE_1__ ppa_struct ;

/* Variables and functions */
 int PPA_SELECT_TMO ; 
 int r_str (unsigned short) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 
 int /*<<< orphan*/  w_dtr (unsigned short,int) ; 

__attribute__((used)) static int ppa_select(ppa_struct *dev, int target)
{
	int k;
	unsigned short ppb = dev->base;

	/*
	 * Bit 6 (0x40) is the device selected bit.
	 * First we must wait till the current device goes off line...
	 */
	k = PPA_SELECT_TMO;
	do {
		k--;
		udelay(1);
	} while ((r_str(ppb) & 0x40) && (k));
	if (!k)
		return 0;

	w_dtr(ppb, (1 << target));
	w_ctr(ppb, 0xe);
	w_ctr(ppb, 0xc);
	w_dtr(ppb, 0x80);	/* This is NOT the initator */
	w_ctr(ppb, 0x8);

	k = PPA_SELECT_TMO;
	do {
		k--;
		udelay(1);
	}
	while (!(r_str(ppb) & 0x40) && (k));
	if (!k)
		return 0;

	return 1;
}