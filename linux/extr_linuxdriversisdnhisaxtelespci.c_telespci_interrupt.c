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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_char ;
struct TYPE_3__ {scalar_t__ membase; } ;
struct TYPE_4__ {TYPE_1__ teles0; } ;
struct IsdnCardState {int /*<<< orphan*/  lock; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HSCX_ISTA ; 
 int /*<<< orphan*/  HSCX_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISAC_ISTA ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  hscx_int_main (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  isac_interrupt (struct IsdnCardState*,int) ; 
 int readhscx (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int readisac (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writehscx (scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeisac (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t
telespci_interrupt(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	u_char hval, ival;
	u_long flags;

	spin_lock_irqsave(&cs->lock, flags);
	hval = readhscx(cs->hw.teles0.membase, 1, HSCX_ISTA);
	if (hval)
		hscx_int_main(cs, hval);
	ival = readisac(cs->hw.teles0.membase, ISAC_ISTA);
	if ((hval | ival) == 0) {
		spin_unlock_irqrestore(&cs->lock, flags);
		return IRQ_NONE;
	}
	if (ival)
		isac_interrupt(cs, ival);
	/* Clear interrupt register for Zoran PCI controller */
	writel(0x70000000, cs->hw.teles0.membase + 0x3C);

	writehscx(cs->hw.teles0.membase, 0, HSCX_MASK, 0xFF);
	writehscx(cs->hw.teles0.membase, 1, HSCX_MASK, 0xFF);
	writeisac(cs->hw.teles0.membase, ISAC_MASK, 0xFF);
	writeisac(cs->hw.teles0.membase, ISAC_MASK, 0x0);
	writehscx(cs->hw.teles0.membase, 0, HSCX_MASK, 0x0);
	writehscx(cs->hw.teles0.membase, 1, HSCX_MASK, 0x0);
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}