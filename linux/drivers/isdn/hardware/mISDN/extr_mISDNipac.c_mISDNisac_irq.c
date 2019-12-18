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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  err_tx; } ;
struct isac_hw {int type; TYPE_1__ dch; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int IPAC_TYPE_ISACX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISACX_CMDRD ; 
 int /*<<< orphan*/  ISACX_CMDRD_RMC ; 
 int ISACX_D_RFO ; 
 int ISACX_D_RME ; 
 int ISACX_D_RPF ; 
 int ISACX_D_XDU ; 
 int ISACX_D_XMR ; 
 int ISACX_D_XPR ; 
 int /*<<< orphan*/  ISACX_ISTAD ; 
 int ISACX__CIC ; 
 int ISACX__ICD ; 
 int /*<<< orphan*/  ISAC_EXIR ; 
 int ReadISAC (struct isac_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteISAC (struct isac_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isac_cisq_irq (struct isac_hw*) ; 
 int /*<<< orphan*/  isac_empty_fifo (struct isac_hw*,int) ; 
 int /*<<< orphan*/  isac_mos_irq (struct isac_hw*) ; 
 int /*<<< orphan*/  isac_retransmit (struct isac_hw*) ; 
 int /*<<< orphan*/  isac_rme_irq (struct isac_hw*) ; 
 int /*<<< orphan*/  isac_xpr_irq (struct isac_hw*) ; 
 int /*<<< orphan*/  isacsx_cic_irq (struct isac_hw*) ; 
 int /*<<< orphan*/  isacsx_rme_irq (struct isac_hw*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ unlikely (int) ; 

irqreturn_t
mISDNisac_irq(struct isac_hw *isac, u8 val)
{
	if (unlikely(!val))
		return IRQ_NONE;
	pr_debug("%s: ISAC interrupt %02x\n", isac->name, val);
	if (isac->type & IPAC_TYPE_ISACX) {
		if (val & ISACX__CIC)
			isacsx_cic_irq(isac);
		if (val & ISACX__ICD) {
			val = ReadISAC(isac, ISACX_ISTAD);
			pr_debug("%s: ISTAD %02x\n", isac->name, val);
			if (val & ISACX_D_XDU) {
				pr_debug("%s: ISAC XDU\n", isac->name);
#ifdef ERROR_STATISTIC
				isac->dch.err_tx++;
#endif
				isac_retransmit(isac);
			}
			if (val & ISACX_D_XMR) {
				pr_debug("%s: ISAC XMR\n", isac->name);
#ifdef ERROR_STATISTIC
				isac->dch.err_tx++;
#endif
				isac_retransmit(isac);
			}
			if (val & ISACX_D_XPR)
				isac_xpr_irq(isac);
			if (val & ISACX_D_RFO) {
				pr_debug("%s: ISAC RFO\n", isac->name);
				WriteISAC(isac, ISACX_CMDRD, ISACX_CMDRD_RMC);
			}
			if (val & ISACX_D_RME)
				isacsx_rme_irq(isac);
			if (val & ISACX_D_RPF)
				isac_empty_fifo(isac, 0x20);
		}
	} else {
		if (val & 0x80)	/* RME */
			isac_rme_irq(isac);
		if (val & 0x40)	/* RPF */
			isac_empty_fifo(isac, 32);
		if (val & 0x10)	/* XPR */
			isac_xpr_irq(isac);
		if (val & 0x04)	/* CISQ */
			isac_cisq_irq(isac);
		if (val & 0x20)	/* RSC - never */
			pr_debug("%s: ISAC RSC interrupt\n", isac->name);
		if (val & 0x02)	/* SIN - never */
			pr_debug("%s: ISAC SIN interrupt\n", isac->name);
		if (val & 0x01) {	/* EXI */
			val = ReadISAC(isac, ISAC_EXIR);
			pr_debug("%s: ISAC EXIR %02x\n", isac->name, val);
			if (val & 0x80)	/* XMR */
				pr_debug("%s: ISAC XMR\n", isac->name);
			if (val & 0x40) { /* XDU */
				pr_debug("%s: ISAC XDU\n", isac->name);
#ifdef ERROR_STATISTIC
				isac->dch.err_tx++;
#endif
				isac_retransmit(isac);
			}
			if (val & 0x04)	/* MOS */
				isac_mos_irq(isac);
		}
	}
	return IRQ_HANDLED;
}