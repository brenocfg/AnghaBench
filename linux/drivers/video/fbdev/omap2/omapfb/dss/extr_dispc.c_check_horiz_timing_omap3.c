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
typedef  int u8 ;
typedef  unsigned long u64 ;
typedef  scalar_t__ u16 ;
struct omap_video_timings {scalar_t__ x_res; scalar_t__ hfp; scalar_t__ hsw; scalar_t__ hbp; } ;

/* Variables and functions */
 int DIV_ROUND_UP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DSSDBG (char*,unsigned long,int const) ; 
 int EINVAL ; 
 unsigned long div_u64 (unsigned long,unsigned long) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int check_horiz_timing_omap3(unsigned long pclk, unsigned long lclk,
		const struct omap_video_timings *t, u16 pos_x,
		u16 width, u16 height, u16 out_width, u16 out_height,
		bool five_taps)
{
	const int ds = DIV_ROUND_UP(height, out_height);
	unsigned long nonactive;
	static const u8 limits[3] = { 8, 10, 20 };
	u64 val, blank;
	int i;

	nonactive = t->x_res + t->hfp + t->hsw + t->hbp - out_width;

	i = 0;
	if (out_height < height)
		i++;
	if (out_width < width)
		i++;
	blank = div_u64((u64)(t->hbp + t->hsw + t->hfp) * lclk, pclk);
	DSSDBG("blanking period + ppl = %llu (limit = %u)\n", blank, limits[i]);
	if (blank <= limits[i])
		return -EINVAL;

	/* FIXME add checks for 3-tap filter once the limitations are known */
	if (!five_taps)
		return 0;

	/*
	 * Pixel data should be prepared before visible display point starts.
	 * So, atleast DS-2 lines must have already been fetched by DISPC
	 * during nonactive - pos_x period.
	 */
	val = div_u64((u64)(nonactive - pos_x) * lclk, pclk);
	DSSDBG("(nonactive - pos_x) * pcd = %llu max(0, DS - 2) * width = %d\n",
		val, max(0, ds - 2) * width);
	if (val < max(0, ds - 2) * width)
		return -EINVAL;

	/*
	 * All lines need to be refilled during the nonactive period of which
	 * only one line can be loaded during the active period. So, atleast
	 * DS - 1 lines should be loaded during nonactive period.
	 */
	val =  div_u64((u64)nonactive * lclk, pclk);
	DSSDBG("nonactive * pcd  = %llu, max(0, DS - 1) * width = %d\n",
		val, max(0, ds - 1) * width);
	if (val < max(0, ds - 1) * width)
		return -EINVAL;

	return 0;
}