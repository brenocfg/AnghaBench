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
typedef  enum output_format_class { ____Placeholder_output_format_class } output_format_class ;

/* Variables and functions */
 int dm_420 ; 
 int dm_n422 ; 
 int dm_s422 ; 
 unsigned int dml_round (unsigned int) ; 

__attribute__((used)) static unsigned int dscceComputeDelay(
		unsigned int bpc,
		double bpp,
		unsigned int sliceWidth,
		unsigned int numSlices,
		enum output_format_class pixelFormat)
{
	// valid bpc         = source bits per component in the set of {8, 10, 12}
	// valid bpp         = increments of 1/16 of a bit
	//                    min = 6/7/8 in N420/N422/444, respectively
	//                    max = such that compression is 1:1
	//valid sliceWidth  = number of pixels per slice line, must be less than or equal to 5184/numSlices (or 4096/numSlices in 420 mode)
	//valid numSlices   = number of slices in the horiziontal direction per DSC engine in the set of {1, 2, 3, 4}
	//valid pixelFormat = pixel/color format in the set of {:N444_RGB, :S422, :N422, :N420}

	// fixed value
	unsigned int rcModelSize = 8192;

	// N422/N420 operate at 2 pixels per clock
	unsigned int pixelsPerClock, lstall, D, initalXmitDelay, w, s, ix, wx, p, l0, a, ax, l,
			Delay, pixels;

	if (pixelFormat == dm_n422 || pixelFormat == dm_420)
		pixelsPerClock = 2;
	// #all other modes operate at 1 pixel per clock
	else
		pixelsPerClock = 1;

	//initial transmit delay as per PPS
	initalXmitDelay = dml_round(rcModelSize / 2.0 / bpp / pixelsPerClock);

	//compute ssm delay
	if (bpc == 8)
		D = 81;
	else if (bpc == 10)
		D = 89;
	else
		D = 113;

	//divide by pixel per cycle to compute slice width as seen by DSC
	w = sliceWidth / pixelsPerClock;

	//422 mode has an additional cycle of delay
	if (pixelFormat == dm_s422)
		s = 1;
	else
		s = 0;

	//main calculation for the dscce
	ix = initalXmitDelay + 45;
	wx = (w + 2) / 3;
	p = 3 * wx - w;
	l0 = ix / w;
	a = ix + p * l0;
	ax = (a + 2) / 3 + D + 6 + 1;
	l = (ax + wx - 1) / wx;
	if ((ix % w) == 0 && p != 0)
		lstall = 1;
	else
		lstall = 0;
	Delay = l * wx * (numSlices - 1) + ax + s + lstall + 22;

	//dsc processes 3 pixel containers per cycle and a container can contain 1 or 2 pixels
	pixels = Delay * 3 * pixelsPerClock;
	return pixels;
}