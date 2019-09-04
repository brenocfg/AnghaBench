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
struct TYPE_3__ {int mocr; int adf2; int /*<<< orphan*/ * mon_rx; int /*<<< orphan*/ * mon_tx; } ;
struct TYPE_4__ {TYPE_1__ isac; } ;
struct IsdnCardState {int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;TYPE_2__ dc; int /*<<< orphan*/  HW_Flags; int /*<<< orphan*/  DC_Close; int /*<<< orphan*/  setstack_d; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_Close_isac ; 
 int /*<<< orphan*/  HW_IOM1 ; 
 int /*<<< orphan*/  ISAC_ADF1 ; 
 int /*<<< orphan*/  ISAC_ADF2 ; 
 int /*<<< orphan*/  ISAC_CMD_RS ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  ISAC_MODE ; 
 int /*<<< orphan*/  ISAC_SPCR ; 
 int /*<<< orphan*/  ISAC_SQXR ; 
 int /*<<< orphan*/  ISAC_STCR ; 
 int /*<<< orphan*/  ISAC_TIMR ; 
 int /*<<< orphan*/  ph_command (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setstack_isac ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub11 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub12 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub13 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub14 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void initisac(struct IsdnCardState *cs)
{
	cs->setstack_d = setstack_isac;
	cs->DC_Close = DC_Close_isac;
	cs->dc.isac.mon_tx = NULL;
	cs->dc.isac.mon_rx = NULL;
	cs->writeisac(cs, ISAC_MASK, 0xff);
	cs->dc.isac.mocr = 0xaa;
	if (test_bit(HW_IOM1, &cs->HW_Flags)) {
		/* IOM 1 Mode */
		cs->writeisac(cs, ISAC_ADF2, 0x0);
		cs->writeisac(cs, ISAC_SPCR, 0xa);
		cs->writeisac(cs, ISAC_ADF1, 0x2);
		cs->writeisac(cs, ISAC_STCR, 0x70);
		cs->writeisac(cs, ISAC_MODE, 0xc9);
	} else {
		/* IOM 2 Mode */
		if (!cs->dc.isac.adf2)
			cs->dc.isac.adf2 = 0x80;
		cs->writeisac(cs, ISAC_ADF2, cs->dc.isac.adf2);
		cs->writeisac(cs, ISAC_SQXR, 0x2f);
		cs->writeisac(cs, ISAC_SPCR, 0x00);
		cs->writeisac(cs, ISAC_STCR, 0x70);
		cs->writeisac(cs, ISAC_MODE, 0xc9);
		cs->writeisac(cs, ISAC_TIMR, 0x00);
		cs->writeisac(cs, ISAC_ADF1, 0x00);
	}
	ph_command(cs, ISAC_CMD_RS);
	cs->writeisac(cs, ISAC_MASK, 0x0);
}