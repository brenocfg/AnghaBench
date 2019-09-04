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
struct TYPE_3__ {int ph_state; } ;
struct TYPE_4__ {TYPE_1__ isac; } ;
struct IsdnCardState {int (* readisac ) (struct IsdnCardState*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;TYPE_2__ dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_L1STATECHANGE ; 
 int /*<<< orphan*/  ISAC_ADF2 ; 
 int /*<<< orphan*/  ISAC_CIR0 ; 
 int /*<<< orphan*/  ISAC_EXIR ; 
 int /*<<< orphan*/  ISAC_ISTA ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  ISAC_MODE ; 
 int /*<<< orphan*/  ISAC_STAR ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int) ; 
 int /*<<< orphan*/  schedule_event (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int stub1 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int stub2 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int stub3 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int stub4 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int stub5 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int stub6 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

void clear_pending_isac_ints(struct IsdnCardState *cs)
{
	int val, eval;

	val = cs->readisac(cs, ISAC_STAR);
	debugl1(cs, "ISAC STAR %x", val);
	val = cs->readisac(cs, ISAC_MODE);
	debugl1(cs, "ISAC MODE %x", val);
	val = cs->readisac(cs, ISAC_ADF2);
	debugl1(cs, "ISAC ADF2 %x", val);
	val = cs->readisac(cs, ISAC_ISTA);
	debugl1(cs, "ISAC ISTA %x", val);
	if (val & 0x01) {
		eval = cs->readisac(cs, ISAC_EXIR);
		debugl1(cs, "ISAC EXIR %x", eval);
	}
	val = cs->readisac(cs, ISAC_CIR0);
	debugl1(cs, "ISAC CIR0 %x", val);
	cs->dc.isac.ph_state = (val >> 2) & 0xf;
	schedule_event(cs, D_L1STATECHANGE);
	/* Disable all IRQ */
	cs->writeisac(cs, ISAC_MASK, 0xFF);
}