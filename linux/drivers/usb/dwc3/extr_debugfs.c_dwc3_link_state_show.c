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
typedef  int u8 ;
typedef  int u32 ;
struct seq_file {struct dwc3* private; } ;
struct dwc3 {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;
typedef  enum dwc3_link_state { ____Placeholder_dwc3_link_state } dwc3_link_state ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DSTS ; 
 int DWC3_DSTS_CONNECTSPD ; 
 int DWC3_DSTS_SUPERSPEED ; 
 int DWC3_DSTS_USBLNKST (int) ; 
 int /*<<< orphan*/  DWC3_GSTS ; 
 scalar_t__ DWC3_GSTS_CURMOD (int) ; 
 scalar_t__ DWC3_GSTS_CURMOD_DEVICE ; 
 int /*<<< orphan*/  dwc3_gadget_hs_link_string (int) ; 
 int /*<<< orphan*/  dwc3_gadget_link_string (int) ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwc3_link_state_show(struct seq_file *s, void *unused)
{
	struct dwc3		*dwc = s->private;
	unsigned long		flags;
	enum dwc3_link_state	state;
	u32			reg;
	u8			speed;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = dwc3_readl(dwc->regs, DWC3_GSTS);
	if (DWC3_GSTS_CURMOD(reg) != DWC3_GSTS_CURMOD_DEVICE) {
		seq_puts(s, "Not available\n");
		spin_unlock_irqrestore(&dwc->lock, flags);
		return 0;
	}

	reg = dwc3_readl(dwc->regs, DWC3_DSTS);
	state = DWC3_DSTS_USBLNKST(reg);
	speed = reg & DWC3_DSTS_CONNECTSPD;

	seq_printf(s, "%s\n", (speed >= DWC3_DSTS_SUPERSPEED) ?
		   dwc3_gadget_link_string(state) :
		   dwc3_gadget_hs_link_string(state));
	spin_unlock_irqrestore(&dwc->lock, flags);

	return 0;
}