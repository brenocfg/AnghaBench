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
typedef  scalar_t__ u32 ;
typedef  enum tiler_fmt { ____Placeholder_tiler_fmt } tiler_fmt ;
struct TYPE_2__ {scalar_t__ x_shft; scalar_t__ y_shft; } ;

/* Variables and functions */
 scalar_t__ CONT_HEIGHT_BITS ; 
 scalar_t__ CONT_WIDTH_BITS ; 
 int /*<<< orphan*/  DBG (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ MASK (scalar_t__) ; 
 scalar_t__ MASK_XY_FLIP ; 
 scalar_t__ MASK_X_INVERT ; 
 scalar_t__ MASK_Y_INVERT ; 
 scalar_t__ TIL_ADDR (scalar_t__,scalar_t__,int) ; 
 TYPE_1__* geom ; 

__attribute__((used)) static u32 tiler_get_address(enum tiler_fmt fmt, u32 orient, u32 x, u32 y)
{
	u32 x_bits, y_bits, tmp, x_mask, y_mask, alignment;

	x_bits = CONT_WIDTH_BITS - geom[fmt].x_shft;
	y_bits = CONT_HEIGHT_BITS - geom[fmt].y_shft;
	alignment = geom[fmt].x_shft + geom[fmt].y_shft;

	/* validate coordinate */
	x_mask = MASK(x_bits);
	y_mask = MASK(y_bits);

	if (x < 0 || x > x_mask || y < 0 || y > y_mask) {
		DBG("invalid coords: %u < 0 || %u > %u || %u < 0 || %u > %u",
				x, x, x_mask, y, y, y_mask);
		return 0;
	}

	/* account for mirroring */
	if (orient & MASK_X_INVERT)
		x ^= x_mask;
	if (orient & MASK_Y_INVERT)
		y ^= y_mask;

	/* get coordinate address */
	if (orient & MASK_XY_FLIP)
		tmp = ((x << y_bits) + y);
	else
		tmp = ((y << x_bits) + x);

	return TIL_ADDR((tmp << alignment), orient, fmt);
}