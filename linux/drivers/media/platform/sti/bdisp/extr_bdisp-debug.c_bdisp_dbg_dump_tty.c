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
#define  BDISP_ARGB8888 133 
#define  BDISP_NV12 132 
#define  BDISP_RGB565 131 
#define  BDISP_RGB888 130 
#define  BDISP_XRGB8888 129 
#define  BDISP_YUV_3B 128 
 int BLT_TTY_ALPHA_R ; 
 int BLT_TTY_BIG_END ; 
 int BLT_TTY_CHROMA ; 
 int BLT_TTY_COL_MASK ; 
 int BLT_TTY_COL_SHIFT ; 
 int BLT_TTY_CR_NOT_CB ; 
 int BLT_TTY_DITHER ; 
 int BLT_TTY_HSO ; 
 int BLT_TTY_MB ; 
 int BLT_TTY_VSO ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void bdisp_dbg_dump_tty(struct seq_file *s, u32 val)
{
	seq_printf(s, "TTY\t0x%08X\t", val);
	seq_printf(s, "Pitch=%d - ", val & 0xFFFF);

	switch ((val & BLT_TTY_COL_MASK) >> BLT_TTY_COL_SHIFT) {
	case BDISP_RGB565:
		seq_puts(s, "RGB565 - ");
		break;
	case BDISP_RGB888:
		seq_puts(s, "RGB888 - ");
		break;
	case BDISP_XRGB8888:
		seq_puts(s, "xRGB888 - ");
		break;
	case BDISP_ARGB8888:
		seq_puts(s, "ARGB8888 - ");
		break;
	case BDISP_NV12:
		seq_puts(s, "NV12 - ");
		break;
	case BDISP_YUV_3B:
		seq_puts(s, "YUV420P - ");
		break;
	default:
		seq_puts(s, "ColorFormat ??? - ");
		break;
	}

	if (val & BLT_TTY_ALPHA_R)
		seq_puts(s, "AlphaRange - ");
	if (val & BLT_TTY_CR_NOT_CB)
		seq_puts(s, "CrNotCb - ");
	if (val & BLT_TTY_MB)
		seq_puts(s, "MB - ");
	if (val & BLT_TTY_HSO)
		seq_puts(s, "HSO inverse - ");
	if (val & BLT_TTY_VSO)
		seq_puts(s, "VSO inverse - ");
	if (val & BLT_TTY_DITHER)
		seq_puts(s, "Dither - ");
	if (val & BLT_TTY_CHROMA)
		seq_puts(s, "Write CHROMA - ");
	if (val & BLT_TTY_BIG_END)
		seq_puts(s, "BigEndian - ");

	seq_putc(s, '\n');
}