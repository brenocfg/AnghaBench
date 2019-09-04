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
struct yuv_playback_info {int decode_height; int v_filter_1; int v_filter_2; int /*<<< orphan*/  reg_289c; int /*<<< orphan*/  reg_2968; int /*<<< orphan*/  reg_2964; int /*<<< orphan*/  reg_2960; int /*<<< orphan*/  reg_295c; int /*<<< orphan*/  reg_2958; int /*<<< orphan*/  reg_2954; int /*<<< orphan*/  reg_2950; int /*<<< orphan*/  reg_2948; int /*<<< orphan*/  reg_2940; int /*<<< orphan*/  reg_296c; int /*<<< orphan*/  reg_291c; int /*<<< orphan*/  reg_2918; int /*<<< orphan*/  reg_2924; int /*<<< orphan*/  reg_2920; int /*<<< orphan*/  reg_292c; int /*<<< orphan*/  reg_2928; int /*<<< orphan*/  reg_2938; int /*<<< orphan*/  reg_2930; int /*<<< orphan*/  reg_294c; int /*<<< orphan*/  reg_2944; int /*<<< orphan*/  reg_293c; int /*<<< orphan*/  reg_2934; } ;
struct yuv_frame_info {int src_h; int dst_h; int src_y; int dst_y; scalar_t__ interlaced_uv; scalar_t__ interlaced_y; scalar_t__ offset_y; scalar_t__ interlaced; int /*<<< orphan*/  tru_h; } ;
struct ivtv {struct yuv_playback_info yuv_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*,char*,...) ; 
 int /*<<< orphan*/  IVTV_DEBUG_YUV (char*,char*,...) ; 
 int /*<<< orphan*/  ivtv_yuv_filter (struct ivtv*,int,int,int) ; 
 int /*<<< orphan*/  write_reg (int,int) ; 

__attribute__((used)) static void ivtv_yuv_handle_vertical(struct ivtv *itv, struct yuv_frame_info *f)
{
	struct yuv_playback_info *yi = &itv->yuv_info;
	u32 master_height;
	u32 reg_2918, reg_291c, reg_2920, reg_2928;
	u32 reg_2930, reg_2934, reg_293c;
	u32 reg_2940, reg_2944, reg_294c;
	u32 reg_2950, reg_2954, reg_2958, reg_295c;
	u32 reg_2960, reg_2964, reg_2968, reg_296c;
	u32 reg_289c;
	u32 src_major_y, src_minor_y;
	u32 src_major_uv, src_minor_uv;
	u32 reg_2964_base, reg_2968_base;
	int v_filter_1, v_filter_2;

	IVTV_DEBUG_WARN
	    ("Adjust to height %d src_h %d dst_h %d src_y %d dst_y %d\n",
	     f->tru_h, f->src_h, f->dst_h, f->src_y, f->dst_y);

	/* What scaling mode is being used... */
	IVTV_DEBUG_YUV("Scaling mode Y: %s\n",
		       f->interlaced_y ? "Interlaced" : "Progressive");

	IVTV_DEBUG_YUV("Scaling mode UV: %s\n",
		       f->interlaced_uv ? "Interlaced" : "Progressive");

	/* What is the source video being treated as... */
	IVTV_DEBUG_WARN("Source video: %s\n",
			f->interlaced ? "Interlaced" : "Progressive");

	/* We offset into the image using two different index methods, so split
	   the y source coord into two parts. */
	if (f->src_y < 8) {
		src_minor_uv = f->src_y;
		src_major_uv = 0;
	} else {
		src_minor_uv = 8;
		src_major_uv = f->src_y - 8;
	}

	src_minor_y = src_minor_uv;
	src_major_y = src_major_uv;

	if (f->offset_y)
		src_minor_y += 16;

	if (f->interlaced_y)
		reg_2918 = (f->dst_h << 16) | (f->src_h + src_minor_y);
	else
		reg_2918 = (f->dst_h << 16) | ((f->src_h + src_minor_y) << 1);

	if (f->interlaced_uv)
		reg_291c = (f->dst_h << 16) | ((f->src_h + src_minor_uv) >> 1);
	else
		reg_291c = (f->dst_h << 16) | (f->src_h + src_minor_uv);

	reg_2964_base = (src_minor_y * ((f->dst_h << 16) / f->src_h)) >> 14;
	reg_2968_base = (src_minor_uv * ((f->dst_h << 16) / f->src_h)) >> 14;

	if (f->dst_h / 2 >= f->src_h && !f->interlaced_y) {
		master_height = (f->src_h * 0x00400000) / f->dst_h;
		if ((f->src_h * 0x00400000) - (master_height * f->dst_h) >= f->dst_h / 2)
			master_height++;
		reg_2920 = master_height >> 2;
		reg_2928 = master_height >> 3;
		reg_2930 = master_height;
		reg_2940 = master_height >> 1;
		reg_2964_base >>= 3;
		reg_2968_base >>= 3;
		reg_296c = 0x00000000;
	} else if (f->dst_h >= f->src_h) {
		master_height = (f->src_h * 0x00400000) / f->dst_h;
		master_height = (master_height >> 1) + (master_height & 1);
		reg_2920 = master_height >> 2;
		reg_2928 = master_height >> 2;
		reg_2930 = master_height;
		reg_2940 = master_height >> 1;
		reg_296c = 0x00000000;
		if (f->interlaced_y) {
			reg_2964_base >>= 3;
		} else {
			reg_296c++;
			reg_2964_base >>= 2;
		}
		if (f->interlaced_uv)
			reg_2928 >>= 1;
		reg_2968_base >>= 3;
	} else if (f->dst_h >= f->src_h / 2) {
		master_height = (f->src_h * 0x00200000) / f->dst_h;
		master_height = (master_height >> 1) + (master_height & 1);
		reg_2920 = master_height >> 2;
		reg_2928 = master_height >> 2;
		reg_2930 = master_height;
		reg_2940 = master_height;
		reg_296c = 0x00000101;
		if (f->interlaced_y) {
			reg_2964_base >>= 2;
		} else {
			reg_296c++;
			reg_2964_base >>= 1;
		}
		if (f->interlaced_uv)
			reg_2928 >>= 1;
		reg_2968_base >>= 2;
	} else {
		master_height = (f->src_h * 0x00100000) / f->dst_h;
		master_height = (master_height >> 1) + (master_height & 1);
		reg_2920 = master_height >> 2;
		reg_2928 = master_height >> 2;
		reg_2930 = master_height;
		reg_2940 = master_height;
		reg_2964_base >>= 1;
		reg_2968_base >>= 2;
		reg_296c = 0x00000102;
	}

	/* FIXME These registers change depending on scaled / unscaled output
	   We really need to work out what they should be */
	if (f->src_h == f->dst_h) {
		reg_2934 = 0x00020000;
		reg_293c = 0x00100000;
		reg_2944 = 0x00040000;
		reg_294c = 0x000b0000;
	} else {
		reg_2934 = 0x00000FF0;
		reg_293c = 0x00000FF0;
		reg_2944 = 0x00000FF0;
		reg_294c = 0x00000FF0;
	}

	/* The first line to be displayed */
	reg_2950 = 0x00010000 + src_major_y;
	if (f->interlaced_y)
		reg_2950 += 0x00010000;
	reg_2954 = reg_2950 + 1;

	reg_2958 = 0x00010000 + (src_major_y >> 1);
	if (f->interlaced_uv)
		reg_2958 += 0x00010000;
	reg_295c = reg_2958 + 1;

	if (yi->decode_height == 480)
		reg_289c = 0x011e0017;
	else
		reg_289c = 0x01500017;

	if (f->dst_y < 0)
		reg_289c = (reg_289c - ((f->dst_y & ~1)<<15))-(f->dst_y >>1);
	else
		reg_289c = (reg_289c + ((f->dst_y & ~1)<<15))+(f->dst_y >>1);

	/* How much of the source to decode.
	   Take into account the source offset */
	reg_2960 = ((src_minor_y + f->src_h + src_major_y) - 1) |
		(((src_minor_uv + f->src_h + src_major_uv - 1) & ~1) << 15);

	/* Calculate correct value for register 2964 */
	if (f->src_h == f->dst_h) {
		reg_2964 = 1;
	} else {
		reg_2964 = 2 + ((f->dst_h << 1) / f->src_h);
		reg_2964 = (reg_2964 >> 1) + (reg_2964 & 1);
	}
	reg_2968 = (reg_2964 << 16) + reg_2964 + (reg_2964 >> 1);
	reg_2964 = (reg_2964 << 16) + reg_2964 + (reg_2964 * 46 / 94);

	/* Okay, we've wasted time working out the correct value,
	   but if we use it, it fouls the the window alignment.
	   Fudge it to what we want... */
	reg_2964 = 0x00010001 + ((reg_2964 & 0x0000FFFF) - (reg_2964 >> 16));
	reg_2968 = 0x00010001 + ((reg_2968 & 0x0000FFFF) - (reg_2968 >> 16));

	/* Deviate further from what it should be. I find the flicker headache
	   inducing so try to reduce it slightly. Leave 2968 as-is otherwise
	   colours foul. */
	if ((reg_2964 != 0x00010001) && (f->dst_h / 2 <= f->src_h))
		reg_2964 = (reg_2964 & 0xFFFF0000) + ((reg_2964 & 0x0000FFFF) / 2);

	if (!f->interlaced_y)
		reg_2964 -= 0x00010001;
	if (!f->interlaced_uv)
		reg_2968 -= 0x00010001;

	reg_2964 += ((reg_2964_base << 16) | reg_2964_base);
	reg_2968 += ((reg_2968_base << 16) | reg_2968_base);

	/* Select the vertical filter */
	if (f->src_h == f->dst_h) {
		/* An exact size match uses filter 0/1 */
		v_filter_1 = 0;
		v_filter_2 = 1;
	} else {
		/* Figure out which filter to use */
		v_filter_1 = ((f->src_h << 16) / f->dst_h) >> 15;
		v_filter_1 = (v_filter_1 >> 1) + (v_filter_1 & 1);
		/* Only an exact size match can use filter 0 */
		v_filter_1 += !v_filter_1;
		v_filter_2 = v_filter_1;
	}

	write_reg(reg_2934, 0x02934);
	write_reg(reg_293c, 0x0293c);
	IVTV_DEBUG_YUV("Update reg 0x2934 %08x->%08x 0x293c %08x->%08x\n",
		       yi->reg_2934, reg_2934, yi->reg_293c, reg_293c);
	write_reg(reg_2944, 0x02944);
	write_reg(reg_294c, 0x0294c);
	IVTV_DEBUG_YUV("Update reg 0x2944 %08x->%08x 0x294c %08x->%08x\n",
		       yi->reg_2944, reg_2944, yi->reg_294c, reg_294c);

	/* Ensure 2970 is 0 (does it ever change ?) */
/*	write_reg(0,0x02970); */
/*	IVTV_DEBUG_YUV("Update reg 0x2970 %08x->%08x\n", yi->reg_2970, 0); */

	write_reg(reg_2930, 0x02938);
	write_reg(reg_2930, 0x02930);
	IVTV_DEBUG_YUV("Update reg 0x2930 %08x->%08x 0x2938 %08x->%08x\n",
		       yi->reg_2930, reg_2930, yi->reg_2938, reg_2930);

	write_reg(reg_2928, 0x02928);
	write_reg(reg_2928 + 0x514, 0x0292C);
	IVTV_DEBUG_YUV("Update reg 0x2928 %08x->%08x 0x292c %08x->%08x\n",
		       yi->reg_2928, reg_2928, yi->reg_292c, reg_2928 + 0x514);

	write_reg(reg_2920, 0x02920);
	write_reg(reg_2920 + 0x514, 0x02924);
	IVTV_DEBUG_YUV("Update reg 0x2920 %08x->%08x 0x2924 %08x->%08x\n",
		       yi->reg_2920, reg_2920, yi->reg_2924, reg_2920 + 0x514);

	write_reg(reg_2918, 0x02918);
	write_reg(reg_291c, 0x0291C);
	IVTV_DEBUG_YUV("Update reg 0x2918 %08x->%08x 0x291C %08x->%08x\n",
		       yi->reg_2918, reg_2918, yi->reg_291c, reg_291c);

	write_reg(reg_296c, 0x0296c);
	IVTV_DEBUG_YUV("Update reg 0x296c %08x->%08x\n",
		       yi->reg_296c, reg_296c);

	write_reg(reg_2940, 0x02948);
	write_reg(reg_2940, 0x02940);
	IVTV_DEBUG_YUV("Update reg 0x2940 %08x->%08x 0x2948 %08x->%08x\n",
		       yi->reg_2940, reg_2940, yi->reg_2948, reg_2940);

	write_reg(reg_2950, 0x02950);
	write_reg(reg_2954, 0x02954);
	IVTV_DEBUG_YUV("Update reg 0x2950 %08x->%08x 0x2954 %08x->%08x\n",
		       yi->reg_2950, reg_2950, yi->reg_2954, reg_2954);

	write_reg(reg_2958, 0x02958);
	write_reg(reg_295c, 0x0295C);
	IVTV_DEBUG_YUV("Update reg 0x2958 %08x->%08x 0x295C %08x->%08x\n",
		       yi->reg_2958, reg_2958, yi->reg_295c, reg_295c);

	write_reg(reg_2960, 0x02960);
	IVTV_DEBUG_YUV("Update reg 0x2960 %08x->%08x \n",
		       yi->reg_2960, reg_2960);

	write_reg(reg_2964, 0x02964);
	write_reg(reg_2968, 0x02968);
	IVTV_DEBUG_YUV("Update reg 0x2964 %08x->%08x 0x2968 %08x->%08x\n",
		       yi->reg_2964, reg_2964, yi->reg_2968, reg_2968);

	write_reg(reg_289c, 0x0289c);
	IVTV_DEBUG_YUV("Update reg 0x289c %08x->%08x\n",
		       yi->reg_289c, reg_289c);

	/* Only update filter 1 if we really need to */
	if (v_filter_1 != yi->v_filter_1) {
		ivtv_yuv_filter(itv, -1, v_filter_1, -1);
		yi->v_filter_1 = v_filter_1;
	}

	/* Only update filter 2 if we really need to */
	if (v_filter_2 != yi->v_filter_2) {
		ivtv_yuv_filter(itv, -1, -1, v_filter_2);
		yi->v_filter_2 = v_filter_2;
	}
}