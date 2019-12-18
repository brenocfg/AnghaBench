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
typedef  scalar_t__ u32 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 scalar_t__* bdisp_rgb_to_yuv ; 
 scalar_t__* bdisp_yuv_to_rgb ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void bdisp_dbg_dump_ivmx(struct seq_file *s,
				u32 c0, u32 c1, u32 c2, u32 c3)
{
	seq_printf(s, "IVMX0\t0x%08X\n", c0);
	seq_printf(s, "IVMX1\t0x%08X\n", c1);
	seq_printf(s, "IVMX2\t0x%08X\n", c2);
	seq_printf(s, "IVMX3\t0x%08X\t", c3);

	if (!c0 && !c1 && !c2 && !c3) {
		seq_putc(s, '\n');
		return;
	}

	if ((c0 == bdisp_rgb_to_yuv[0]) &&
	    (c1 == bdisp_rgb_to_yuv[1]) &&
	    (c2 == bdisp_rgb_to_yuv[2]) &&
	    (c3 == bdisp_rgb_to_yuv[3])) {
		seq_puts(s, "RGB to YUV\n");
		return;
	}

	if ((c0 == bdisp_yuv_to_rgb[0]) &&
	    (c1 == bdisp_yuv_to_rgb[1]) &&
	    (c2 == bdisp_yuv_to_rgb[2]) &&
	    (c3 == bdisp_yuv_to_rgb[3])) {
		seq_puts(s, "YUV to RGB\n");
		return;
	}
	seq_puts(s, "Unknown conversion\n");
}