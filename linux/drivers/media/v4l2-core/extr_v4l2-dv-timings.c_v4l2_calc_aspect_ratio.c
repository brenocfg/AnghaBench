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
struct v4l2_fract {int member_0; int member_1; int numerator; int denominator; } ;

/* Variables and functions */
 int /*<<< orphan*/  swap (int,int) ; 

struct v4l2_fract v4l2_calc_aspect_ratio(u8 hor_landscape, u8 vert_portrait)
{
	struct v4l2_fract aspect = { 16, 9 };
	u8 ratio;

	/* Nothing filled in, fallback to 16:9 */
	if (!hor_landscape && !vert_portrait)
		return aspect;
	/* Both filled in, so they are interpreted as the screen size in cm */
	if (hor_landscape && vert_portrait) {
		aspect.numerator = hor_landscape;
		aspect.denominator = vert_portrait;
		return aspect;
	}
	/* Only one is filled in, so interpret them as a ratio:
	   (val + 99) / 100 */
	ratio = hor_landscape | vert_portrait;
	/* Change some rounded values into the exact aspect ratio */
	if (ratio == 79) {
		aspect.numerator = 16;
		aspect.denominator = 9;
	} else if (ratio == 34) {
		aspect.numerator = 4;
		aspect.denominator = 3;
	} else if (ratio == 68) {
		aspect.numerator = 15;
		aspect.denominator = 9;
	} else {
		aspect.numerator = hor_landscape + 99;
		aspect.denominator = 100;
	}
	if (hor_landscape)
		return aspect;
	/* The aspect ratio is for portrait, so swap numerator and denominator */
	swap(aspect.denominator, aspect.numerator);
	return aspect;
}