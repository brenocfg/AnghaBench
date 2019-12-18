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
struct dwc3 {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GDBGLSP ; 
 int /*<<< orphan*/  DWC3_GDBGLSPMUX ; 
 int /*<<< orphan*/  DWC3_GDBGLSPMUX_DEVSELECT (int) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_gadget_lsp(struct seq_file *s)
{
	struct dwc3		*dwc = s->private;
	int			i;
	u32			reg;

	for (i = 0; i < 16; i++) {
		reg = DWC3_GDBGLSPMUX_DEVSELECT(i);
		dwc3_writel(dwc->regs, DWC3_GDBGLSPMUX, reg);
		reg = dwc3_readl(dwc->regs, DWC3_GDBGLSP);
		seq_printf(s, "GDBGLSP[%d] = 0x%08x\n", i, reg);
	}
}