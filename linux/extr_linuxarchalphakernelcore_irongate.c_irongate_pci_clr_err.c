#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int stat_cmd; } ;

/* Variables and functions */
 TYPE_1__* IRONGATE0 ; 
 unsigned int* IronECC ; 
 unsigned int inb (int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  outb (unsigned int,int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

int
irongate_pci_clr_err(void)
{
	unsigned int nmi_ctl=0;
	unsigned int IRONGATE_jd;

again:
	IRONGATE_jd = IRONGATE0->stat_cmd;
	printk("Iron stat_cmd %x\n", IRONGATE_jd);
	IRONGATE0->stat_cmd = IRONGATE_jd; /* write again clears error bits */
	mb();
	IRONGATE_jd = IRONGATE0->stat_cmd;  /* re-read to force write */

	IRONGATE_jd = *IronECC;
	printk("Iron ECC %x\n", IRONGATE_jd);
	*IronECC = IRONGATE_jd; /* write again clears error bits */
	mb();
	IRONGATE_jd = *IronECC;  /* re-read to force write */

	/* Clear ALI NMI */
        nmi_ctl = inb(0x61);
        nmi_ctl |= 0x0c;
        outb(nmi_ctl, 0x61);
        nmi_ctl &= ~0x0c;
        outb(nmi_ctl, 0x61);

	IRONGATE_jd = *IronECC;
	if (IRONGATE_jd & 0x300) goto again;

	return 0;
}