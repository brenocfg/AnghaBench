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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 log1_times100(u32 x)
{
	static const u8 scale = 15;
	static const u8 index_width = 5;
	/*
	   log2lut[n] = (1<<scale) * 200 * log2( 1.0 + ( (1.0/(1<<INDEXWIDTH)) * n ))
	   0 <= n < ((1<<INDEXWIDTH)+1)
	 */

	static const u32 log2lut[] = {
		0,		/* 0.000000 */
		290941,		/* 290941.300628 */
		573196,		/* 573196.476418 */
		847269,		/* 847269.179851 */
		1113620,	/* 1113620.489452 */
		1372674,	/* 1372673.576986 */
		1624818,	/* 1624817.752104 */
		1870412,	/* 1870411.981536 */
		2109788,	/* 2109787.962654 */
		2343253,	/* 2343252.817465 */
		2571091,	/* 2571091.461923 */
		2793569,	/* 2793568.696416 */
		3010931,	/* 3010931.055901 */
		3223408,	/* 3223408.452106 */
		3431216,	/* 3431215.635215 */
		3634553,	/* 3634553.498355 */
		3833610,	/* 3833610.244726 */
		4028562,	/* 4028562.434393 */
		4219576,	/* 4219575.925308 */
		4406807,	/* 4406806.721144 */
		4590402,	/* 4590401.736809 */
		4770499,	/* 4770499.491025 */
		4947231,	/* 4947230.734179 */
		5120719,	/* 5120719.018555 */
		5291081,	/* 5291081.217197 */
		5458428,	/* 5458427.996830 */
		5622864,	/* 5622864.249668 */
		5784489,	/* 5784489.488298 */
		5943398,	/* 5943398.207380 */
		6099680,	/* 6099680.215452 */
		6253421,	/* 6253420.939751 */
		6404702,	/* 6404701.706649 */
		6553600,	/* 6553600.000000 */
	};

	u8 i = 0;
	u32 y = 0;
	u32 d = 0;
	u32 k = 0;
	u32 r = 0;

	if (x == 0)
		return 0;

	/* Scale x (normalize) */
	/* computing y in log(x/y) = log(x) - log(y) */
	if ((x & (((u32) (-1)) << (scale + 1))) == 0) {
		for (k = scale; k > 0; k--) {
			if (x & (((u32) 1) << scale))
				break;
			x <<= 1;
		}
	} else {
		for (k = scale; k < 31; k++) {
			if ((x & (((u32) (-1)) << (scale + 1))) == 0)
				break;
			x >>= 1;
		}
	}
	/*
	   Now x has binary point between bit[scale] and bit[scale-1]
	   and 1.0 <= x < 2.0 */

	/* correction for division: log(x) = log(x/y)+log(y) */
	y = k * ((((u32) 1) << scale) * 200);

	/* remove integer part */
	x &= ((((u32) 1) << scale) - 1);
	/* get index */
	i = (u8) (x >> (scale - index_width));
	/* compute delta (x-a) */
	d = x & ((((u32) 1) << (scale - index_width)) - 1);
	/* compute log, multiplication ( d* (.. )) must be within range ! */
	y += log2lut[i] +
	    ((d * (log2lut[i + 1] - log2lut[i])) >> (scale - index_width));
	/* Conver to log10() */
	y /= 108853;		/* (log2(10) << scale) */
	r = (y >> 1);
	/* rounding */
	if (y & ((u32)1))
		r++;

	return r;

}