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
struct TYPE_3__ {int ctrl_reg; scalar_t__ cfg; int /*<<< orphan*/  isac; int /*<<< orphan*/  ale; scalar_t__ trig; scalar_t__ timer; scalar_t__ ctrl; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 int ELSA_ISDN_RESET ; 
 scalar_t__ ELSA_PCMCIA_IPAC ; 
 scalar_t__ ELSA_QS1000PCI ; 
 scalar_t__ ELSA_QS3000PCI ; 
 int /*<<< orphan*/  IPAC_ACFG ; 
 int /*<<< orphan*/  IPAC_AOE ; 
 int /*<<< orphan*/  IPAC_ATX ; 
 int /*<<< orphan*/  IPAC_MASK ; 
 int /*<<< orphan*/  IPAC_PCFG ; 
 int /*<<< orphan*/  IPAC_POTA2 ; 
 scalar_t__ TimerRun (struct IsdnCardState*) ; 
 int /*<<< orphan*/  byteout (scalar_t__,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
reset_elsa(struct IsdnCardState *cs)
{
	if (cs->hw.elsa.timer) {
		/* Wait 1 Timer */
		byteout(cs->hw.elsa.timer, 0);
		while (TimerRun(cs));
		cs->hw.elsa.ctrl_reg |= 0x50;
		cs->hw.elsa.ctrl_reg &= ~ELSA_ISDN_RESET;	/* Reset On */
		byteout(cs->hw.elsa.ctrl, cs->hw.elsa.ctrl_reg);
		/* Wait 1 Timer */
		byteout(cs->hw.elsa.timer, 0);
		while (TimerRun(cs));
		cs->hw.elsa.ctrl_reg |= ELSA_ISDN_RESET;	/* Reset Off */
		byteout(cs->hw.elsa.ctrl, cs->hw.elsa.ctrl_reg);
		/* Wait 1 Timer */
		byteout(cs->hw.elsa.timer, 0);
		while (TimerRun(cs));
		if (cs->hw.elsa.trig)
			byteout(cs->hw.elsa.trig, 0xff);
	}
	if ((cs->subtyp == ELSA_QS1000PCI) || (cs->subtyp == ELSA_QS3000PCI) || (cs->subtyp == ELSA_PCMCIA_IPAC)) {
		writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_POTA2, 0x20);
		mdelay(10);
		writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_POTA2, 0x00);
		writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_MASK, 0xc0);
		mdelay(10);
		if (cs->subtyp != ELSA_PCMCIA_IPAC) {
			writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_ACFG, 0x0);
			writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_AOE, 0x3c);
		} else {
			writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_PCFG, 0x10);
			writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_ACFG, 0x4);
			writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_AOE, 0xf8);
		}
		writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_ATX, 0xff);
		if (cs->subtyp == ELSA_QS1000PCI)
			byteout(cs->hw.elsa.cfg + 0x4c, 0x41); /* enable ELSA PCI IRQ */
		else if (cs->subtyp == ELSA_QS3000PCI)
			byteout(cs->hw.elsa.cfg + 0x4c, 0x43); /* enable ELSA PCI IRQ */
	}
}