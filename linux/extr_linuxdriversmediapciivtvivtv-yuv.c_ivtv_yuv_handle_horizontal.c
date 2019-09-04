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
struct yuv_playback_info {int h_filter; int /*<<< orphan*/  reg_2890; int /*<<< orphan*/  reg_2870; int /*<<< orphan*/  reg_2874; int /*<<< orphan*/  reg_2864; int /*<<< orphan*/  reg_285c; int /*<<< orphan*/  reg_2854; int /*<<< orphan*/  reg_2848; int /*<<< orphan*/  reg_2840; int /*<<< orphan*/  reg_2844; int /*<<< orphan*/  reg_283c; int /*<<< orphan*/  reg_2838; int /*<<< orphan*/  reg_2834; } ;
struct yuv_frame_info {int src_w; int dst_w; int src_x; int dst_x; int vis_w; int tru_x; int pan_x; int /*<<< orphan*/  tru_w; } ;
struct ivtv {struct yuv_playback_info yuv_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  IVTV_DEBUG_YUV (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  ivtv_yuv_filter (struct ivtv*,int,int,int) ; 
 int /*<<< orphan*/  write_reg (int,int) ; 

__attribute__((used)) static void ivtv_yuv_handle_horizontal(struct ivtv *itv, struct yuv_frame_info *f)
{
	struct yuv_playback_info *yi = &itv->yuv_info;
	u32 reg_2834, reg_2838, reg_283c;
	u32 reg_2844, reg_2854, reg_285c;
	u32 reg_2864, reg_2874, reg_2890;
	u32 reg_2870, reg_2870_base, reg_2870_offset;
	int x_cutoff;
	int h_filter;
	u32 master_width;

	IVTV_DEBUG_WARN
	    ("Adjust to width %d src_w %d dst_w %d src_x %d dst_x %d\n",
	     f->tru_w, f->src_w, f->dst_w, f->src_x, f->dst_x);

	/* How wide is the src image */
	x_cutoff = f->src_w + f->src_x;

	/* Set the display width */
	reg_2834 = f->dst_w;
	reg_2838 = reg_2834;

	/* Set the display position */
	reg_2890 = f->dst_x;

	/* Index into the image horizontally */
	reg_2870 = 0;

	/* 2870 is normally fudged to align video coords with osd coords.
	   If running full screen, it causes an unwanted left shift
	   Remove the fudge if we almost fill the screen.
	   Gradually adjust the offset to avoid the video 'snapping'
	   left/right if it gets dragged through this region.
	   Only do this if osd is full width. */
	if (f->vis_w == 720) {
		if ((f->tru_x - f->pan_x > -1) && (f->tru_x - f->pan_x <= 40) && (f->dst_w >= 680))
			reg_2870 = 10 - (f->tru_x - f->pan_x) / 4;
		else if ((f->tru_x - f->pan_x < 0) && (f->tru_x - f->pan_x >= -20) && (f->dst_w >= 660))
			reg_2870 = (10 + (f->tru_x - f->pan_x) / 2);

		if (f->dst_w >= f->src_w)
			reg_2870 = reg_2870 << 16 | reg_2870;
		else
			reg_2870 = ((reg_2870 & ~1) << 15) | (reg_2870 & ~1);
	}

	if (f->dst_w < f->src_w)
		reg_2870 = 0x000d000e - reg_2870;
	else
		reg_2870 = 0x0012000e - reg_2870;

	/* We're also using 2870 to shift the image left (src_x & negative dst_x) */
	reg_2870_offset = (f->src_x * ((f->dst_w << 21) / f->src_w)) >> 19;

	if (f->dst_w >= f->src_w) {
		x_cutoff &= ~1;
		master_width = (f->src_w * 0x00200000) / (f->dst_w);
		if (master_width * f->dst_w != f->src_w * 0x00200000)
			master_width++;
		reg_2834 = (reg_2834 << 16) | x_cutoff;
		reg_2838 = (reg_2838 << 16) | x_cutoff;
		reg_283c = master_width >> 2;
		reg_2844 = master_width >> 2;
		reg_2854 = master_width;
		reg_285c = master_width >> 1;
		reg_2864 = master_width >> 1;

		/* We also need to factor in the scaling
		   (src_w - dst_w) / (src_w / 4) */
		if (f->dst_w > f->src_w)
			reg_2870_base = ((f->dst_w - f->src_w)<<16) / (f->src_w <<14);
		else
			reg_2870_base = 0;

		reg_2870 += (((reg_2870_offset << 14) & 0xFFFF0000) | reg_2870_offset >> 2) + (reg_2870_base << 17 | reg_2870_base);
		reg_2874 = 0;
	} else if (f->dst_w < f->src_w / 2) {
		master_width = (f->src_w * 0x00080000) / f->dst_w;
		if (master_width * f->dst_w != f->src_w * 0x00080000)
			master_width++;
		reg_2834 = (reg_2834 << 16) | x_cutoff;
		reg_2838 = (reg_2838 << 16) | x_cutoff;
		reg_283c = master_width >> 2;
		reg_2844 = master_width >> 1;
		reg_2854 = master_width;
		reg_285c = master_width >> 1;
		reg_2864 = master_width >> 1;
		reg_2870 += ((reg_2870_offset << 15) & 0xFFFF0000) | reg_2870_offset;
		reg_2870 += (5 - (((f->src_w + f->src_w / 2) - 1) / f->dst_w)) << 16;
		reg_2874 = 0x00000012;
	} else {
		master_width = (f->src_w * 0x00100000) / f->dst_w;
		if (master_width * f->dst_w != f->src_w * 0x00100000)
			master_width++;
		reg_2834 = (reg_2834 << 16) | x_cutoff;
		reg_2838 = (reg_2838 << 16) | x_cutoff;
		reg_283c = master_width >> 2;
		reg_2844 = master_width >> 1;
		reg_2854 = master_width;
		reg_285c = master_width >> 1;
		reg_2864 = master_width >> 1;
		reg_2870 += ((reg_2870_offset << 14) & 0xFFFF0000) | reg_2870_offset >> 1;
		reg_2870 += (5 - (((f->src_w * 3) - 1) / f->dst_w)) << 16;
		reg_2874 = 0x00000001;
	}

	/* Select the horizontal filter */
	if (f->src_w == f->dst_w) {
		/* An exact size match uses filter 0 */
		h_filter = 0;
	} else {
		/* Figure out which filter to use */
		h_filter = ((f->src_w << 16) / f->dst_w) >> 15;
		h_filter = (h_filter >> 1) + (h_filter & 1);
		/* Only an exact size match can use filter 0 */
		h_filter += !h_filter;
	}

	write_reg(reg_2834, 0x02834);
	write_reg(reg_2838, 0x02838);
	IVTV_DEBUG_YUV("Update reg 0x2834 %08x->%08x 0x2838 %08x->%08x\n",
		       yi->reg_2834, reg_2834, yi->reg_2838, reg_2838);

	write_reg(reg_283c, 0x0283c);
	write_reg(reg_2844, 0x02844);

	IVTV_DEBUG_YUV("Update reg 0x283c %08x->%08x 0x2844 %08x->%08x\n",
		       yi->reg_283c, reg_283c, yi->reg_2844, reg_2844);

	write_reg(0x00080514, 0x02840);
	write_reg(0x00100514, 0x02848);
	IVTV_DEBUG_YUV("Update reg 0x2840 %08x->%08x 0x2848 %08x->%08x\n",
		       yi->reg_2840, 0x00080514, yi->reg_2848, 0x00100514);

	write_reg(reg_2854, 0x02854);
	IVTV_DEBUG_YUV("Update reg 0x2854 %08x->%08x \n",
		       yi->reg_2854, reg_2854);

	write_reg(reg_285c, 0x0285c);
	write_reg(reg_2864, 0x02864);
	IVTV_DEBUG_YUV("Update reg 0x285c %08x->%08x 0x2864 %08x->%08x\n",
		       yi->reg_285c, reg_285c, yi->reg_2864, reg_2864);

	write_reg(reg_2874, 0x02874);
	IVTV_DEBUG_YUV("Update reg 0x2874 %08x->%08x\n",
		       yi->reg_2874, reg_2874);

	write_reg(reg_2870, 0x02870);
	IVTV_DEBUG_YUV("Update reg 0x2870 %08x->%08x\n",
		       yi->reg_2870, reg_2870);

	write_reg(reg_2890, 0x02890);
	IVTV_DEBUG_YUV("Update reg 0x2890 %08x->%08x\n",
		       yi->reg_2890, reg_2890);

	/* Only update the filter if we really need to */
	if (h_filter != yi->h_filter) {
		ivtv_yuv_filter(itv, h_filter, -1, -1);
		yi->h_filter = h_filter;
	}
}