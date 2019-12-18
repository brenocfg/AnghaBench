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
struct lynx_accel {scalar_t__ (* de_wait ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DE_BACKGROUND ; 
 int /*<<< orphan*/  DE_CONTROL ; 
 int DE_CONTROL_COMMAND_HOST_WRITE ; 
 int DE_CONTROL_HOST ; 
 int DE_CONTROL_ROP_MASK ; 
 int DE_CONTROL_ROP_SELECT ; 
 int DE_CONTROL_STATUS ; 
 int /*<<< orphan*/  DE_DESTINATION ; 
 int DE_DESTINATION_X_MASK ; 
 int DE_DESTINATION_X_SHIFT ; 
 int DE_DESTINATION_Y_MASK ; 
 int /*<<< orphan*/  DE_DIMENSION ; 
 int DE_DIMENSION_X_MASK ; 
 int DE_DIMENSION_X_SHIFT ; 
 int DE_DIMENSION_Y_ET_MASK ; 
 int /*<<< orphan*/  DE_FOREGROUND ; 
 int /*<<< orphan*/  DE_PITCH ; 
 int DE_PITCH_DESTINATION_MASK ; 
 int DE_PITCH_DESTINATION_SHIFT ; 
 int DE_PITCH_SOURCE_MASK ; 
 int /*<<< orphan*/  DE_SOURCE ; 
 int DE_SOURCE_X_K1_MONO_MASK ; 
 int DE_SOURCE_X_K1_SHIFT ; 
 int /*<<< orphan*/  DE_WINDOW_DESTINATION_BASE ; 
 int /*<<< orphan*/  DE_WINDOW_SOURCE_BASE ; 
 int /*<<< orphan*/  DE_WINDOW_WIDTH ; 
 int DE_WINDOW_WIDTH_DST_MASK ; 
 int DE_WINDOW_WIDTH_DST_SHIFT ; 
 int DE_WINDOW_WIDTH_SRC_MASK ; 
 unsigned int deGetTransparency (struct lynx_accel*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,unsigned int) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  write_dpPort (struct lynx_accel*,unsigned int) ; 
 int /*<<< orphan*/  write_dpr (struct lynx_accel*,int /*<<< orphan*/ ,unsigned int) ; 

int sm750_hw_imageblit(struct lynx_accel *accel,
		 const char *pSrcbuf, /* pointer to start of source buffer in system memory */
		 u32 srcDelta,          /* Pitch value (in bytes) of the source buffer, +ive means top down and -ive mean button up */
		 u32 startBit, /* Mono data can start at any bit in a byte, this value should be 0 to 7 */
		 u32 dBase,    /* Address of destination: offset in frame buffer */
		 u32 dPitch,   /* Pitch value of destination surface in BYTE */
		 u32 bytePerPixel,      /* Color depth of destination surface */
		 u32 dx,
		 u32 dy,       /* Starting coordinate of destination surface */
		 u32 width,
		 u32 height,   /* width and height of rectangle in pixel value */
		 u32 fColor,   /* Foreground color (corresponding to a 1 in the monochrome data */
		 u32 bColor,   /* Background color (corresponding to a 0 in the monochrome data */
		 u32 rop2)     /* ROP value */
{
	unsigned int ulBytesPerScan;
	unsigned int ul4BytesPerScan;
	unsigned int ulBytesRemain;
	unsigned int de_ctrl = 0;
	unsigned char ajRemain[4];
	int i, j;

	startBit &= 7; /* Just make sure the start bit is within legal range */
	ulBytesPerScan = (width + startBit + 7) / 8;
	ul4BytesPerScan = ulBytesPerScan & ~3;
	ulBytesRemain = ulBytesPerScan & 3;

	if (accel->de_wait() != 0)
		return -1;

	/*
	 * 2D Source Base.
	 * Use 0 for HOST Blt.
	 */
	write_dpr(accel, DE_WINDOW_SOURCE_BASE, 0);

	/* 2D Destination Base.
	 * It is an address offset (128 bit aligned)
	 * from the beginning of frame buffer.
	 */
	write_dpr(accel, DE_WINDOW_DESTINATION_BASE, dBase);

	/*
	 * Program pitch (distance between the 1st points of two adjacent
	 * lines). Note that input pitch is BYTE value, but the 2D Pitch
	 * register uses pixel values. Need Byte to pixel conversion.
	 */
	write_dpr(accel, DE_PITCH,
		  ((dPitch / bytePerPixel << DE_PITCH_DESTINATION_SHIFT) &
		   DE_PITCH_DESTINATION_MASK) |
		  (dPitch / bytePerPixel & DE_PITCH_SOURCE_MASK)); /* dpr10 */

	/*
	 * Screen Window width in Pixels.
	 * 2D engine uses this value to calculate the linear address
	 * in frame buffer for a given point.
	 */
	write_dpr(accel, DE_WINDOW_WIDTH,
		  ((dPitch / bytePerPixel << DE_WINDOW_WIDTH_DST_SHIFT) &
		   DE_WINDOW_WIDTH_DST_MASK) |
		  (dPitch / bytePerPixel & DE_WINDOW_WIDTH_SRC_MASK));

	 /*
	  * Note: For 2D Source in Host Write, only X_K1_MONO field is needed,
	  * and Y_K2 field is not used.
	  * For mono bitmap, use startBit for X_K1.
	  */
	write_dpr(accel, DE_SOURCE,
		  (startBit << DE_SOURCE_X_K1_SHIFT) &
		  DE_SOURCE_X_K1_MONO_MASK); /* dpr00 */

	write_dpr(accel, DE_DESTINATION,
		  ((dx << DE_DESTINATION_X_SHIFT) & DE_DESTINATION_X_MASK) |
		  (dy & DE_DESTINATION_Y_MASK)); /* dpr04 */

	write_dpr(accel, DE_DIMENSION,
		  ((width << DE_DIMENSION_X_SHIFT) & DE_DIMENSION_X_MASK) |
		  (height & DE_DIMENSION_Y_ET_MASK)); /* dpr08 */

	write_dpr(accel, DE_FOREGROUND, fColor);
	write_dpr(accel, DE_BACKGROUND, bColor);

	de_ctrl = (rop2 & DE_CONTROL_ROP_MASK) |
		DE_CONTROL_ROP_SELECT | DE_CONTROL_COMMAND_HOST_WRITE |
		DE_CONTROL_HOST | DE_CONTROL_STATUS;

	write_dpr(accel, DE_CONTROL, de_ctrl | deGetTransparency(accel));

	/* Write MONO data (line by line) to 2D Engine data port */
	for (i = 0; i < height; i++) {
		/* For each line, send the data in chunks of 4 bytes */
		for (j = 0; j < (ul4BytesPerScan / 4); j++)
			write_dpPort(accel, *(unsigned int *)(pSrcbuf + (j * 4)));

		if (ulBytesRemain) {
			memcpy(ajRemain, pSrcbuf + ul4BytesPerScan,
			       ulBytesRemain);
			write_dpPort(accel, *(unsigned int *)ajRemain);
		}

		pSrcbuf += srcDelta;
	}

	return 0;
}