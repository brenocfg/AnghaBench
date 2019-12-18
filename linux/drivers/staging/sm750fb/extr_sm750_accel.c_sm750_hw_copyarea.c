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
struct lynx_accel {scalar_t__ (* de_wait ) () ;} ;

/* Variables and functions */
 unsigned int BOTTOM_TO_TOP ; 
 int /*<<< orphan*/  DE_CONTROL ; 
 unsigned int DE_CONTROL_COMMAND_BITBLT ; 
 unsigned int DE_CONTROL_DIRECTION ; 
 unsigned int DE_CONTROL_ROP_MASK ; 
 unsigned int DE_CONTROL_ROP_SELECT ; 
 unsigned int DE_CONTROL_STATUS ; 
 int /*<<< orphan*/  DE_DESTINATION ; 
 unsigned int DE_DESTINATION_X_MASK ; 
 unsigned int DE_DESTINATION_X_SHIFT ; 
 unsigned int DE_DESTINATION_Y_MASK ; 
 int /*<<< orphan*/  DE_DIMENSION ; 
 unsigned int DE_DIMENSION_X_MASK ; 
 unsigned int DE_DIMENSION_X_SHIFT ; 
 unsigned int DE_DIMENSION_Y_ET_MASK ; 
 int /*<<< orphan*/  DE_PITCH ; 
 unsigned int DE_PITCH_DESTINATION_MASK ; 
 unsigned int DE_PITCH_DESTINATION_SHIFT ; 
 unsigned int DE_PITCH_SOURCE_MASK ; 
 int /*<<< orphan*/  DE_SOURCE ; 
 unsigned int DE_SOURCE_X_K1_MASK ; 
 unsigned int DE_SOURCE_X_K1_SHIFT ; 
 unsigned int DE_SOURCE_Y_K2_MASK ; 
 int /*<<< orphan*/  DE_WINDOW_DESTINATION_BASE ; 
 int /*<<< orphan*/  DE_WINDOW_SOURCE_BASE ; 
 int /*<<< orphan*/  DE_WINDOW_WIDTH ; 
 unsigned int DE_WINDOW_WIDTH_DST_MASK ; 
 unsigned int DE_WINDOW_WIDTH_DST_SHIFT ; 
 unsigned int DE_WINDOW_WIDTH_SRC_MASK ; 
 unsigned int LEFT_TO_RIGHT ; 
 unsigned int RIGHT_TO_LEFT ; 
 unsigned int TOP_TO_BOTTOM ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  write_dpr (struct lynx_accel*,int /*<<< orphan*/ ,unsigned int) ; 

int sm750_hw_copyarea(
struct lynx_accel *accel,
unsigned int sBase,  /* Address of source: offset in frame buffer */
unsigned int sPitch, /* Pitch value of source surface in BYTE */
unsigned int sx,
unsigned int sy,     /* Starting coordinate of source surface */
unsigned int dBase,  /* Address of destination: offset in frame buffer */
unsigned int dPitch, /* Pitch value of destination surface in BYTE */
unsigned int Bpp,    /* Color depth of destination surface */
unsigned int dx,
unsigned int dy,     /* Starting coordinate of destination surface */
unsigned int width,
unsigned int height, /* width and height of rectangle in pixel value */
unsigned int rop2)   /* ROP value */
{
	unsigned int nDirection, de_ctrl;

	nDirection = LEFT_TO_RIGHT;
	/* Direction of ROP2 operation: 1 = Left to Right, (-1) = Right to Left */
	de_ctrl = 0;

	/* If source and destination are the same surface, need to check for overlay cases */
	if (sBase == dBase && sPitch == dPitch) {
		/* Determine direction of operation */
		if (sy < dy) {
			/*  +----------+
			 *  |S         |
			 *  |   +----------+
			 *  |   |      |   |
			 *  |   |      |   |
			 *  +---|------+   |
			 *	|         D|
			 *	+----------+
			 */

			nDirection = BOTTOM_TO_TOP;
		} else if (sy > dy) {
			/*  +----------+
			 *  |D         |
			 *  |   +----------+
			 *  |   |      |   |
			 *  |   |      |   |
			 *  +---|------+   |
			 *	|         S|
			 *	+----------+
			 */

			nDirection = TOP_TO_BOTTOM;
		} else {
			/* sy == dy */

			if (sx <= dx) {
				/* +------+---+------+
				 * |S     |   |     D|
				 * |      |   |      |
				 * |      |   |      |
				 * |      |   |      |
				 * +------+---+------+
				 */

				nDirection = RIGHT_TO_LEFT;
			} else {
			/* sx > dx */

				/* +------+---+------+
				 * |D     |   |     S|
				 * |      |   |      |
				 * |      |   |      |
				 * |      |   |      |
				 * +------+---+------+
				 */

				nDirection = LEFT_TO_RIGHT;
			}
		}
	}

	if ((nDirection == BOTTOM_TO_TOP) || (nDirection == RIGHT_TO_LEFT)) {
		sx += width - 1;
		sy += height - 1;
		dx += width - 1;
		dy += height - 1;
	}

	/*
	 * Note:
	 * DE_FOREGROUND are DE_BACKGROUND are don't care.
	 * DE_COLOR_COMPARE and DE_COLOR_COMPARE_MAKS
	 * are set by set deSetTransparency().
	 */

	/*
	 * 2D Source Base.
	 * It is an address offset (128 bit aligned)
	 * from the beginning of frame buffer.
	 */
	write_dpr(accel, DE_WINDOW_SOURCE_BASE, sBase); /* dpr40 */

	/*
	 * 2D Destination Base.
	 * It is an address offset (128 bit aligned)
	 * from the beginning of frame buffer.
	 */
	write_dpr(accel, DE_WINDOW_DESTINATION_BASE, dBase); /* dpr44 */

    /*
     * Program pitch (distance between the 1st points of two adjacent lines).
     * Note that input pitch is BYTE value, but the 2D Pitch register uses
     * pixel values. Need Byte to pixel conversion.
     */
	write_dpr(accel, DE_PITCH,
		  ((dPitch / Bpp << DE_PITCH_DESTINATION_SHIFT) &
		   DE_PITCH_DESTINATION_MASK) |
		  (sPitch / Bpp & DE_PITCH_SOURCE_MASK)); /* dpr10 */

    /*
     * Screen Window width in Pixels.
     * 2D engine uses this value to calculate the linear address in frame buffer
     * for a given point.
     */
	write_dpr(accel, DE_WINDOW_WIDTH,
		  ((dPitch / Bpp << DE_WINDOW_WIDTH_DST_SHIFT) &
		   DE_WINDOW_WIDTH_DST_MASK) |
		  (sPitch / Bpp & DE_WINDOW_WIDTH_SRC_MASK)); /* dpr3c */

	if (accel->de_wait() != 0)
		return -1;

	write_dpr(accel, DE_SOURCE,
		  ((sx << DE_SOURCE_X_K1_SHIFT) & DE_SOURCE_X_K1_MASK) |
		  (sy & DE_SOURCE_Y_K2_MASK)); /* dpr0 */
	write_dpr(accel, DE_DESTINATION,
		  ((dx << DE_DESTINATION_X_SHIFT) & DE_DESTINATION_X_MASK) |
		  (dy & DE_DESTINATION_Y_MASK)); /* dpr04 */
	write_dpr(accel, DE_DIMENSION,
		  ((width << DE_DIMENSION_X_SHIFT) & DE_DIMENSION_X_MASK) |
		  (height & DE_DIMENSION_Y_ET_MASK)); /* dpr08 */

	de_ctrl = (rop2 & DE_CONTROL_ROP_MASK) | DE_CONTROL_ROP_SELECT |
		((nDirection == RIGHT_TO_LEFT) ? DE_CONTROL_DIRECTION : 0) |
		DE_CONTROL_COMMAND_BITBLT | DE_CONTROL_STATUS;
	write_dpr(accel, DE_CONTROL, de_ctrl); /* dpr0c */

	return 0;
}