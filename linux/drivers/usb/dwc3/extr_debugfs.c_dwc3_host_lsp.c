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
typedef  int u32 ;
struct seq_file {struct dwc3* private; } ;
struct TYPE_2__ {int hwparams1; } ;
struct dwc3 {int dbg_lsp_select; int /*<<< orphan*/  regs; TYPE_1__ hwparams; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GDBGLSP ; 
 int /*<<< orphan*/  DWC3_GDBGLSPMUX ; 
 int DWC3_GDBGLSPMUX_ENDBC ; 
 int DWC3_GDBGLSPMUX_HOSTSELECT (int) ; 
 int DWC3_GHWPARAMS1_ENDBC ; 
 int DWC3_LSP_MUX_UNSELECTED ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void dwc3_host_lsp(struct seq_file *s)
{
	struct dwc3		*dwc = s->private;
	bool			dbc_enabled;
	u32			sel;
	u32			reg;
	u32			val;

	dbc_enabled = !!(dwc->hwparams.hwparams1 & DWC3_GHWPARAMS1_ENDBC);

	sel = dwc->dbg_lsp_select;
	if (sel == DWC3_LSP_MUX_UNSELECTED) {
		seq_puts(s, "Write LSP selection to print for host\n");
		return;
	}

	reg = DWC3_GDBGLSPMUX_HOSTSELECT(sel);

	dwc3_writel(dwc->regs, DWC3_GDBGLSPMUX, reg);
	val = dwc3_readl(dwc->regs, DWC3_GDBGLSP);
	seq_printf(s, "GDBGLSP[%d] = 0x%08x\n", sel, val);

	if (dbc_enabled && sel < 256) {
		reg |= DWC3_GDBGLSPMUX_ENDBC;
		dwc3_writel(dwc->regs, DWC3_GDBGLSPMUX, reg);
		val = dwc3_readl(dwc->regs, DWC3_GDBGLSP);
		seq_printf(s, "GDBGLSP_DBC[%d] = 0x%08x\n", sel, val);
	}
}