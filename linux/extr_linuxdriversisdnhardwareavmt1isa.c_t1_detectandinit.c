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

/* Variables and functions */
 int HEMA_PAL_ID ; 
 int HEMA_VERSION_ID ; 
 unsigned int T1_ANALYSE ; 
 unsigned int T1_FASTLINK ; 
 scalar_t__ T1_FIFOSTAT ; 
 scalar_t__ T1_IDENT ; 
 scalar_t__ T1_INSTAT ; 
 scalar_t__ T1_IRQENABLE ; 
 scalar_t__ T1_IRQMASTER ; 
 scalar_t__ T1_OUTSTAT ; 
 unsigned int T1_RESETBOARD ; 
 unsigned int T1_RESETLINK ; 
 unsigned int T1_SLOWLINK ; 
 unsigned char* hema_irq_table ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int t1inp (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  t1outp (unsigned int,unsigned int,int) ; 

__attribute__((used)) static int t1_detectandinit(unsigned int base, unsigned irq, int cardnr)
{
	unsigned char cregs[8];
	unsigned char reverse_cardnr;
	unsigned char dummy;
	int i;

	reverse_cardnr =   ((cardnr & 0x01) << 3) | ((cardnr & 0x02) << 1)
		| ((cardnr & 0x04) >> 1) | ((cardnr & 0x08) >> 3);
	cregs[0] = (HEMA_VERSION_ID << 4) | (reverse_cardnr & 0xf);
	cregs[1] = 0x00; /* fast & slow link connected to CON1 */
	cregs[2] = 0x05; /* fast link 20MBit, slow link 20 MBit */
	cregs[3] = 0;
	cregs[4] = 0x11; /* zero wait state */
	cregs[5] = hema_irq_table[irq & 0xf];
	cregs[6] = 0;
	cregs[7] = 0;

	/*
	 * no one else should use the ISA bus in this moment,
	 * but no function there to prevent this :-(
	 * save_flags(flags); cli();
	 */

	/* board reset */
	t1outp(base, T1_RESETBOARD, 0xf);
	mdelay(100);
	dummy = t1inp(base, T1_FASTLINK + T1_OUTSTAT); /* first read */

	/* write config */
	dummy = (base >> 4) & 0xff;
	for (i = 1; i <= 0xf; i++) t1outp(base, i, dummy);
	t1outp(base, HEMA_PAL_ID & 0xf, dummy);
	t1outp(base, HEMA_PAL_ID >> 4, cregs[0]);
	for (i = 1; i < 7; i++) t1outp(base, 0, cregs[i]);
	t1outp(base, ((base >> 4)) & 0x3, cregs[7]);
	/* restore_flags(flags); */

	mdelay(100);
	t1outp(base, T1_FASTLINK + T1_RESETLINK, 0);
	t1outp(base, T1_SLOWLINK + T1_RESETLINK, 0);
	mdelay(10);
	t1outp(base, T1_FASTLINK + T1_RESETLINK, 1);
	t1outp(base, T1_SLOWLINK + T1_RESETLINK, 1);
	mdelay(100);
	t1outp(base, T1_FASTLINK + T1_RESETLINK, 0);
	t1outp(base, T1_SLOWLINK + T1_RESETLINK, 0);
	mdelay(10);
	t1outp(base, T1_FASTLINK + T1_ANALYSE, 0);
	mdelay(5);
	t1outp(base, T1_SLOWLINK + T1_ANALYSE, 0);

	if (t1inp(base, T1_FASTLINK + T1_OUTSTAT) != 0x1) /* tx empty */
		return 1;
	if (t1inp(base, T1_FASTLINK + T1_INSTAT) != 0x0) /* rx empty */
		return 2;
	if (t1inp(base, T1_FASTLINK + T1_IRQENABLE) != 0x0)
		return 3;
	if ((t1inp(base, T1_FASTLINK + T1_FIFOSTAT) & 0xf0) != 0x70)
		return 4;
	if ((t1inp(base, T1_FASTLINK + T1_IRQMASTER) & 0x0e) != 0)
		return 5;
	if ((t1inp(base, T1_FASTLINK + T1_IDENT) & 0x7d) != 1)
		return 6;
	if (t1inp(base, T1_SLOWLINK + T1_OUTSTAT) != 0x1) /* tx empty */
		return 7;
	if ((t1inp(base, T1_SLOWLINK + T1_IRQMASTER) & 0x0e) != 0)
		return 8;
	if ((t1inp(base, T1_SLOWLINK + T1_IDENT) & 0x7d) != 0)
		return 9;
	return 0;
}