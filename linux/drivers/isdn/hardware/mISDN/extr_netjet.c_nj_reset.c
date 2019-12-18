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
struct tiger_hw {scalar_t__ typ; int ctrlreg; int auxd; scalar_t__ base; scalar_t__ dmactrl; } ;

/* Variables and functions */
 scalar_t__ NETJET_S_TJ320 ; 
 scalar_t__ NJ_AUXCTRL ; 
 scalar_t__ NJ_AUXDATA ; 
 scalar_t__ NJ_CTRL ; 
 scalar_t__ NJ_IRQMASK1 ; 
 int NJ_ISACIRQ ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void
nj_reset(struct tiger_hw *card)
{
	outb(0xff, card->base + NJ_CTRL); /* Reset On */
	mdelay(1);

	/* now edge triggered for TJ320 GE 13/07/00 */
	/* see comment in IRQ function */
	if (card->typ == NETJET_S_TJ320) /* TJ320 */
		card->ctrlreg = 0x40;  /* Reset Off and status read clear */
	else
		card->ctrlreg = 0x00;  /* Reset Off and status read clear */
	outb(card->ctrlreg, card->base + NJ_CTRL);
	mdelay(10);

	/* configure AUX pins (all output except ISAC IRQ pin) */
	card->auxd = 0;
	card->dmactrl = 0;
	outb(~NJ_ISACIRQ, card->base + NJ_AUXCTRL);
	outb(NJ_ISACIRQ,  card->base + NJ_IRQMASK1);
	outb(card->auxd, card->base + NJ_AUXDATA);
}