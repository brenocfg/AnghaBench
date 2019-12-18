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
typedef  int u32 ;
typedef  enum tiler_fmt { ____Placeholder_tiler_fmt } tiler_fmt ;
struct TYPE_2__ {int x_shft; int y_shft; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CONT_HEIGHT_BITS ; 
 int CONT_WIDTH_BITS ; 
 int MASK_XY_FLIP ; 
 TYPE_1__* geom ; 
 int /*<<< orphan*/  validfmt (int) ; 

u32 tiler_stride(enum tiler_fmt fmt, u32 orient)
{
	BUG_ON(!validfmt(fmt));

	if (orient & MASK_XY_FLIP)
		return 1 << (CONT_HEIGHT_BITS + geom[fmt].x_shft);
	else
		return 1 << (CONT_WIDTH_BITS + geom[fmt].y_shft);
}