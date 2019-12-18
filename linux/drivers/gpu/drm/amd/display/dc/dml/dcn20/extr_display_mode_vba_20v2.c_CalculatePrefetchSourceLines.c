#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  IgnoreViewportPositioning; } ;
struct display_mode_lib {TYPE_1__ vba; } ;

/* Variables and functions */
 double dml_ceil (double,int) ; 
 double dml_floor (double,int) ; 
 unsigned int dml_max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dml_print (char*) ; 

__attribute__((used)) static double CalculatePrefetchSourceLines(
		struct display_mode_lib *mode_lib,
		double VRatio,
		double vtaps,
		bool Interlace,
		bool ProgressiveToInterlaceUnitInOPP,
		unsigned int SwathHeight,
		unsigned int ViewportYStart,
		double *VInitPreFill,
		unsigned int *MaxNumSwath)
{
	unsigned int MaxPartialSwath;

	if (ProgressiveToInterlaceUnitInOPP)
		*VInitPreFill = dml_floor((VRatio + vtaps + 1) / 2.0, 1);
	else
		*VInitPreFill = dml_floor((VRatio + vtaps + 1 + Interlace * 0.5 * VRatio) / 2.0, 1);

	if (!mode_lib->vba.IgnoreViewportPositioning) {

		*MaxNumSwath = dml_ceil((*VInitPreFill - 1.0) / SwathHeight, 1) + 1.0;

		if (*VInitPreFill > 1.0)
			MaxPartialSwath = (unsigned int) (*VInitPreFill - 2) % SwathHeight;
		else
			MaxPartialSwath = (unsigned int) (*VInitPreFill + SwathHeight - 2)
					% SwathHeight;
		MaxPartialSwath = dml_max(1U, MaxPartialSwath);

	} else {

		if (ViewportYStart != 0)
			dml_print(
					"WARNING DML: using viewport y position of 0 even though actual viewport y position is non-zero in prefetch source lines calculation\n");

		*MaxNumSwath = dml_ceil(*VInitPreFill / SwathHeight, 1);

		if (*VInitPreFill > 1.0)
			MaxPartialSwath = (unsigned int) (*VInitPreFill - 1) % SwathHeight;
		else
			MaxPartialSwath = (unsigned int) (*VInitPreFill + SwathHeight - 1)
					% SwathHeight;
	}

	return *MaxNumSwath * SwathHeight + MaxPartialSwath;
}