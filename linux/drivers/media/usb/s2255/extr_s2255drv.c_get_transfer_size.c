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
struct s2255_mode {scalar_t__ format; int scale; int color; } ;

/* Variables and functions */
 int COLOR_Y8 ; 
 int DEF_USB_BLOCK ; 
 scalar_t__ FORMAT_NTSC ; 
 scalar_t__ FORMAT_PAL ; 
 int LINE_SZ_1CIFS_NTSC ; 
 int LINE_SZ_1CIFS_PAL ; 
 int LINE_SZ_2CIFS_NTSC ; 
 int LINE_SZ_2CIFS_PAL ; 
 int LINE_SZ_4CIFS_NTSC ; 
 int LINE_SZ_4CIFS_PAL ; 
 int LINE_SZ_DEF ; 
 int MASK_COLOR ; 
 int NUM_LINES_1CIFS_NTSC ; 
 int NUM_LINES_1CIFS_PAL ; 
 int NUM_LINES_2CIFS_NTSC ; 
 int NUM_LINES_2CIFS_PAL ; 
 int NUM_LINES_4CIFS_NTSC ; 
 int NUM_LINES_4CIFS_PAL ; 
 int NUM_LINES_DEF ; 
 int PREFIX_SIZE ; 
#define  SCALE_1CIFS 131 
#define  SCALE_2CIFS 130 
#define  SCALE_4CIFS 129 
#define  SCALE_4CIFSI 128 

__attribute__((used)) static u32 get_transfer_size(struct s2255_mode *mode)
{
	int linesPerFrame = LINE_SZ_DEF;
	int pixelsPerLine = NUM_LINES_DEF;
	u32 outImageSize;
	u32 usbInSize;
	unsigned int mask_mult;

	if (mode == NULL)
		return 0;

	if (mode->format == FORMAT_NTSC) {
		switch (mode->scale) {
		case SCALE_4CIFS:
		case SCALE_4CIFSI:
			linesPerFrame = NUM_LINES_4CIFS_NTSC * 2;
			pixelsPerLine = LINE_SZ_4CIFS_NTSC;
			break;
		case SCALE_2CIFS:
			linesPerFrame = NUM_LINES_2CIFS_NTSC;
			pixelsPerLine = LINE_SZ_2CIFS_NTSC;
			break;
		case SCALE_1CIFS:
			linesPerFrame = NUM_LINES_1CIFS_NTSC;
			pixelsPerLine = LINE_SZ_1CIFS_NTSC;
			break;
		default:
			break;
		}
	} else if (mode->format == FORMAT_PAL) {
		switch (mode->scale) {
		case SCALE_4CIFS:
		case SCALE_4CIFSI:
			linesPerFrame = NUM_LINES_4CIFS_PAL * 2;
			pixelsPerLine = LINE_SZ_4CIFS_PAL;
			break;
		case SCALE_2CIFS:
			linesPerFrame = NUM_LINES_2CIFS_PAL;
			pixelsPerLine = LINE_SZ_2CIFS_PAL;
			break;
		case SCALE_1CIFS:
			linesPerFrame = NUM_LINES_1CIFS_PAL;
			pixelsPerLine = LINE_SZ_1CIFS_PAL;
			break;
		default:
			break;
		}
	}
	outImageSize = linesPerFrame * pixelsPerLine;
	if ((mode->color & MASK_COLOR) != COLOR_Y8) {
		/* 2 bytes/pixel if not monochrome */
		outImageSize *= 2;
	}

	/* total bytes to send including prefix and 4K padding;
	   must be a multiple of USB_READ_SIZE */
	usbInSize = outImageSize + PREFIX_SIZE;	/* always send prefix */
	mask_mult = 0xffffffffUL - DEF_USB_BLOCK + 1;
	/* if size not a multiple of USB_READ_SIZE */
	if (usbInSize & ~mask_mult)
		usbInSize = (usbInSize & mask_mult) + (DEF_USB_BLOCK);
	return usbInSize;
}