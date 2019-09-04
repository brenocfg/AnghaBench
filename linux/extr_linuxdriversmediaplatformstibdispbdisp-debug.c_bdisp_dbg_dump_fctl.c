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
typedef  int u32 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int BLT_FCTL_HV_SAMPLE ; 
 int BLT_FCTL_HV_SCALE ; 
 int BLT_FCTL_Y_HV_SAMPLE ; 
 int BLT_FCTL_Y_HV_SCALE ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void bdisp_dbg_dump_fctl(struct seq_file *s, u32 val)
{
	seq_printf(s, "FCTL\t0x%08X\t", val);

	if ((val & BLT_FCTL_Y_HV_SCALE) == BLT_FCTL_Y_HV_SCALE)
		seq_puts(s, "Resize Luma - ");
	else if ((val & BLT_FCTL_Y_HV_SCALE) == BLT_FCTL_Y_HV_SAMPLE)
		seq_puts(s, "Sample Luma - ");

	if ((val & BLT_FCTL_HV_SCALE) == BLT_FCTL_HV_SCALE)
		seq_puts(s, "Resize Chroma");
	else if ((val & BLT_FCTL_HV_SCALE) == BLT_FCTL_HV_SAMPLE)
		seq_puts(s, "Sample Chroma");

	seq_putc(s, '\n');
}