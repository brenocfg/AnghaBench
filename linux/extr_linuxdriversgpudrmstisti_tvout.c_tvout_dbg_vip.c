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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int TVO_VIP_CLIP_MASK ; 
 int TVO_VIP_CLIP_SHIFT ; 
 int TVO_VIP_REORDER_B_SHIFT ; 
 size_t TVO_VIP_REORDER_CB_B_SEL ; 
 size_t TVO_VIP_REORDER_CR_R_SEL ; 
 int TVO_VIP_REORDER_G_SHIFT ; 
 int TVO_VIP_REORDER_MASK ; 
 int TVO_VIP_REORDER_R_SHIFT ; 
 size_t TVO_VIP_REORDER_Y_G_SEL ; 
 int TVO_VIP_RND_MASK ; 
 int TVO_VIP_RND_SHIFT ; 
 int TVO_VIP_SEL_INPUT_MASK ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char* const,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void tvout_dbg_vip(struct seq_file *s, int val)
{
	int r, g, b, tmp, mask;
	char *const reorder[] = {"Y_G", "Cb_B", "Cr_R"};
	char *const clipping[] = {"No", "EAV/SAV", "Limited range RGB/Y",
				  "Limited range Cb/Cr", "decided by register"};
	char *const round[] = {"8-bit", "10-bit", "12-bit"};
	char *const input_sel[] = {"Main (color matrix enabled)",
				   "Main (color matrix by-passed)",
				   "", "", "", "", "", "",
				   "Aux (color matrix enabled)",
				   "Aux (color matrix by-passed)",
				   "", "", "", "", "", "Force value"};

	seq_putc(s, '\t');
	mask = TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_R_SHIFT;
	r = (val & mask) >> TVO_VIP_REORDER_R_SHIFT;
	mask = TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_G_SHIFT;
	g = (val & mask) >> TVO_VIP_REORDER_G_SHIFT;
	mask = TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_B_SHIFT;
	b = (val & mask) >> TVO_VIP_REORDER_B_SHIFT;
	seq_printf(s, "%-24s %s->%s %s->%s %s->%s\n", "Reorder:",
		   reorder[r], reorder[TVO_VIP_REORDER_CR_R_SEL],
		   reorder[g], reorder[TVO_VIP_REORDER_Y_G_SEL],
		   reorder[b], reorder[TVO_VIP_REORDER_CB_B_SEL]);
	seq_puts(s, "\t\t\t\t\t");
	mask = TVO_VIP_CLIP_MASK << TVO_VIP_CLIP_SHIFT;
	tmp = (val & mask) >> TVO_VIP_CLIP_SHIFT;
	seq_printf(s, "%-24s %s\n", "Clipping:", clipping[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	mask = TVO_VIP_RND_MASK << TVO_VIP_RND_SHIFT;
	tmp = (val & mask) >> TVO_VIP_RND_SHIFT;
	seq_printf(s, "%-24s input data rounded to %s per component\n",
		   "Round:", round[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (val & TVO_VIP_SEL_INPUT_MASK);
	seq_printf(s, "%-24s %s", "Input selection:", input_sel[tmp]);
}