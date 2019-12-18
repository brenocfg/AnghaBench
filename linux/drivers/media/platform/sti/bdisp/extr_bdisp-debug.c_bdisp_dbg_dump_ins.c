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
 int BLT_INS_AQLOCK ; 
 int BLT_INS_CKEY ; 
 int BLT_INS_CLIP ; 
 int BLT_INS_CLUT ; 
 int BLT_INS_DEI ; 
 int BLT_INS_FLICK ; 
 int BLT_INS_GRAD ; 
 int BLT_INS_IRQ ; 
 int BLT_INS_IVMX ; 
 int BLT_INS_OVMX ; 
 int BLT_INS_PACE ; 
 int BLT_INS_PMASK ; 
 int BLT_INS_ROTATE ; 
#define  BLT_INS_S1_CF 135 
#define  BLT_INS_S1_COPY 134 
#define  BLT_INS_S1_FILL 133 
 int BLT_INS_S1_MASK ; 
#define  BLT_INS_S1_MEM 132 
#define  BLT_INS_S1_OFF 131 
#define  BLT_INS_S2_CF 130 
 int BLT_INS_S2_MASK ; 
#define  BLT_INS_S2_MEM 129 
#define  BLT_INS_S2_OFF 128 
 int BLT_INS_S3_MASK ; 
 int BLT_INS_S3_MEM ; 
 int BLT_INS_SCALE ; 
 int BLT_INS_VC1R ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void bdisp_dbg_dump_ins(struct seq_file *s, u32 val)
{
	seq_printf(s, "INS\t0x%08X\t", val);

	switch (val & BLT_INS_S1_MASK) {
	case BLT_INS_S1_OFF:
		break;
	case BLT_INS_S1_MEM:
		seq_puts(s, "SRC1=mem - ");
		break;
	case BLT_INS_S1_CF:
		seq_puts(s, "SRC1=ColorFill - ");
		break;
	case BLT_INS_S1_COPY:
		seq_puts(s, "SRC1=copy - ");
		break;
	case BLT_INS_S1_FILL:
		seq_puts(s, "SRC1=fil - ");
		break;
	default:
		seq_puts(s, "SRC1=??? - ");
		break;
	}

	switch (val & BLT_INS_S2_MASK) {
	case BLT_INS_S2_OFF:
		break;
	case BLT_INS_S2_MEM:
		seq_puts(s, "SRC2=mem - ");
		break;
	case BLT_INS_S2_CF:
		seq_puts(s, "SRC2=ColorFill - ");
		break;
	default:
		seq_puts(s, "SRC2=??? - ");
		break;
	}

	if ((val & BLT_INS_S3_MASK) == BLT_INS_S3_MEM)
		seq_puts(s, "SRC3=mem - ");

	if (val & BLT_INS_IVMX)
		seq_puts(s, "IVMX - ");
	if (val & BLT_INS_CLUT)
		seq_puts(s, "CLUT - ");
	if (val & BLT_INS_SCALE)
		seq_puts(s, "Scale - ");
	if (val & BLT_INS_FLICK)
		seq_puts(s, "Flicker - ");
	if (val & BLT_INS_CLIP)
		seq_puts(s, "Clip - ");
	if (val & BLT_INS_CKEY)
		seq_puts(s, "ColorKey - ");
	if (val & BLT_INS_OVMX)
		seq_puts(s, "OVMX - ");
	if (val & BLT_INS_DEI)
		seq_puts(s, "Deint - ");
	if (val & BLT_INS_PMASK)
		seq_puts(s, "PlaneMask - ");
	if (val & BLT_INS_VC1R)
		seq_puts(s, "VC1R - ");
	if (val & BLT_INS_ROTATE)
		seq_puts(s, "Rotate - ");
	if (val & BLT_INS_GRAD)
		seq_puts(s, "GradFill - ");
	if (val & BLT_INS_AQLOCK)
		seq_puts(s, "AQLock - ");
	if (val & BLT_INS_PACE)
		seq_puts(s, "Pace - ");
	if (val & BLT_INS_IRQ)
		seq_puts(s, "IRQ - ");

	seq_putc(s, '\n');
}