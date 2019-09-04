#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ctrl_reg; int auxd; scalar_t__ auxa; scalar_t__ base; scalar_t__ dmactrl; scalar_t__ isac; } ;
struct TYPE_4__ {TYPE_1__ njet; } ;
struct IsdnCardState {TYPE_2__ hw; } ;
struct IsdnCard {int dummy; } ;

/* Variables and functions */
 scalar_t__ NETJET_AUXCTRL ; 
 scalar_t__ NETJET_AUXDATA ; 
 scalar_t__ NETJET_CTRL ; 
 scalar_t__ NETJET_IRQMASK1 ; 
 int TJ_AMD_IRQ ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void en_cs_init(struct IsdnCard *card, struct IsdnCardState *cs)
{
	cs->hw.njet.auxa = cs->hw.njet.base + NETJET_AUXDATA;
	cs->hw.njet.isac = cs->hw.njet.base + 0xC0; // Fenster zum AMD

	/* Reset an */
	cs->hw.njet.ctrl_reg = 0x07;  // geändert von 0xff
	outb(cs->hw.njet.ctrl_reg, cs->hw.njet.base + NETJET_CTRL);
	/* 20 ms Pause */
	mdelay(20);

	cs->hw.njet.ctrl_reg = 0x30;  /* Reset Off and status read clear */
	outb(cs->hw.njet.ctrl_reg, cs->hw.njet.base + NETJET_CTRL);
	mdelay(10);

	cs->hw.njet.auxd = 0x00; // war 0xc0
	cs->hw.njet.dmactrl = 0;

	outb(~TJ_AMD_IRQ, cs->hw.njet.base + NETJET_AUXCTRL);
	outb(TJ_AMD_IRQ, cs->hw.njet.base + NETJET_IRQMASK1);
	outb(cs->hw.njet.auxd, cs->hw.njet.auxa);
}