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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {struct dwc3* private; } ;
struct dwc3 {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GSTS ; 
 unsigned int DWC3_GSTS_CURMOD (int /*<<< orphan*/ ) ; 
#define  DWC3_GSTS_CURMOD_DEVICE 129 
#define  DWC3_GSTS_CURMOD_HOST 128 
 int /*<<< orphan*/  dwc3_gadget_lsp (struct seq_file*) ; 
 int /*<<< orphan*/  dwc3_host_lsp (struct seq_file*) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwc3_lsp_show(struct seq_file *s, void *unused)
{
	struct dwc3		*dwc = s->private;
	unsigned int		current_mode;
	unsigned long		flags;
	u32			reg;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = dwc3_readl(dwc->regs, DWC3_GSTS);
	current_mode = DWC3_GSTS_CURMOD(reg);

	switch (current_mode) {
	case DWC3_GSTS_CURMOD_HOST:
		dwc3_host_lsp(s);
		break;
	case DWC3_GSTS_CURMOD_DEVICE:
		dwc3_gadget_lsp(s);
		break;
	default:
		seq_puts(s, "Mode is unknown, no LSP register printed\n");
		break;
	}
	spin_unlock_irqrestore(&dwc->lock, flags);

	return 0;
}