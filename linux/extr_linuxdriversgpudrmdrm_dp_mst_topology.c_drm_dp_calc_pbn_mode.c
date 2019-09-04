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
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int drm_fixp2int_ceil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fixp_from_fraction (int,int) ; 

int drm_dp_calc_pbn_mode(int clock, int bpp)
{
	u64 kbps;
	s64 peak_kbps;
	u32 numerator;
	u32 denominator;

	kbps = clock * bpp;

	/*
	 * margin 5300ppm + 300ppm ~ 0.6% as per spec, factor is 1.006
	 * The unit of 54/64Mbytes/sec is an arbitrary unit chosen based on
	 * common multiplier to render an integer PBN for all link rate/lane
	 * counts combinations
	 * calculate
	 * peak_kbps *= (1006/1000)
	 * peak_kbps *= (64/54)
	 * peak_kbps *= 8    convert to bytes
	 */

	numerator = 64 * 1006;
	denominator = 54 * 8 * 1000 * 1000;

	kbps *= numerator;
	peak_kbps = drm_fixp_from_fraction(kbps, denominator);

	return drm_fixp2int_ceil(peak_kbps);
}