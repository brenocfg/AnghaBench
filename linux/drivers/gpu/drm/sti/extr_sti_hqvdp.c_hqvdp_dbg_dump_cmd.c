#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int config; int config2; int dcdi_config; } ;
struct TYPE_5__ {int output_picture_size; int param_ctrl; int /*<<< orphan*/  cv_coef; int /*<<< orphan*/  yv_coef; int /*<<< orphan*/  ch_coef; int /*<<< orphan*/  yh_coef; } ;
struct TYPE_4__ {int config; int mem_format; int current_luma; int current_chroma; int luma_src_pitch; int chroma_src_pitch; int input_frame_size; int input_viewport_size; } ;
struct sti_hqvdp_cmd {TYPE_3__ csdi; TYPE_2__ hvsrc; TYPE_1__ top; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
#define  CSDI_CONFIG_INTER_DIR 132 
#define  CSDI_CONFIG_PROG 131 
#define  TOP_CONFIG_INTER_BTM 130 
#define  TOP_CONFIG_INTER_TOP 129 
#define  TOP_CONFIG_PROGRESSIVE 128 
 int hqvdp_dbg_get_lut (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void hqvdp_dbg_dump_cmd(struct seq_file *s, struct sti_hqvdp_cmd *c)
{
	int src_w, src_h, dst_w, dst_h;

	seq_puts(s, "\n\tTOP:");
	seq_printf(s, "\n\t %-20s 0x%08X", "Config", c->top.config);
	switch (c->top.config) {
	case TOP_CONFIG_PROGRESSIVE:
		seq_puts(s, "\tProgressive");
		break;
	case TOP_CONFIG_INTER_TOP:
		seq_puts(s, "\tInterlaced, top field");
		break;
	case TOP_CONFIG_INTER_BTM:
		seq_puts(s, "\tInterlaced, bottom field");
		break;
	default:
		seq_puts(s, "\t<UNKNOWN>");
		break;
	}

	seq_printf(s, "\n\t %-20s 0x%08X", "MemFormat", c->top.mem_format);
	seq_printf(s, "\n\t %-20s 0x%08X", "CurrentY", c->top.current_luma);
	seq_printf(s, "\n\t %-20s 0x%08X", "CurrentC", c->top.current_chroma);
	seq_printf(s, "\n\t %-20s 0x%08X", "YSrcPitch", c->top.luma_src_pitch);
	seq_printf(s, "\n\t %-20s 0x%08X", "CSrcPitch",
		   c->top.chroma_src_pitch);
	seq_printf(s, "\n\t %-20s 0x%08X", "InputFrameSize",
		   c->top.input_frame_size);
	seq_printf(s, "\t%dx%d",
		   c->top.input_frame_size & 0x0000FFFF,
		   c->top.input_frame_size >> 16);
	seq_printf(s, "\n\t %-20s 0x%08X", "InputViewportSize",
		   c->top.input_viewport_size);
	src_w = c->top.input_viewport_size & 0x0000FFFF;
	src_h = c->top.input_viewport_size >> 16;
	seq_printf(s, "\t%dx%d", src_w, src_h);

	seq_puts(s, "\n\tHVSRC:");
	seq_printf(s, "\n\t %-20s 0x%08X", "OutputPictureSize",
		   c->hvsrc.output_picture_size);
	dst_w = c->hvsrc.output_picture_size & 0x0000FFFF;
	dst_h = c->hvsrc.output_picture_size >> 16;
	seq_printf(s, "\t%dx%d", dst_w, dst_h);
	seq_printf(s, "\n\t %-20s 0x%08X", "ParamCtrl", c->hvsrc.param_ctrl);

	seq_printf(s, "\n\t %-20s %s", "yh_coef",
		   hqvdp_dbg_get_lut(c->hvsrc.yh_coef));
	seq_printf(s, "\n\t %-20s %s", "ch_coef",
		   hqvdp_dbg_get_lut(c->hvsrc.ch_coef));
	seq_printf(s, "\n\t %-20s %s", "yv_coef",
		   hqvdp_dbg_get_lut(c->hvsrc.yv_coef));
	seq_printf(s, "\n\t %-20s %s", "cv_coef",
		   hqvdp_dbg_get_lut(c->hvsrc.cv_coef));

	seq_printf(s, "\n\t %-20s", "ScaleH");
	if (dst_w > src_w)
		seq_printf(s, " %d/1", dst_w / src_w);
	else
		seq_printf(s, " 1/%d", src_w / dst_w);

	seq_printf(s, "\n\t %-20s", "tScaleV");
	if (dst_h > src_h)
		seq_printf(s, " %d/1", dst_h / src_h);
	else
		seq_printf(s, " 1/%d", src_h / dst_h);

	seq_puts(s, "\n\tCSDI:");
	seq_printf(s, "\n\t %-20s 0x%08X\t", "Config", c->csdi.config);
	switch (c->csdi.config) {
	case CSDI_CONFIG_PROG:
		seq_puts(s, "Bypass");
		break;
	case CSDI_CONFIG_INTER_DIR:
		seq_puts(s, "Deinterlace, directional");
		break;
	default:
		seq_puts(s, "<UNKNOWN>");
		break;
	}

	seq_printf(s, "\n\t %-20s 0x%08X", "Config2", c->csdi.config2);
	seq_printf(s, "\n\t %-20s 0x%08X", "DcdiConfig", c->csdi.dcdi_config);
}