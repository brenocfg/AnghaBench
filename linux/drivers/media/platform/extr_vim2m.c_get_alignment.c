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

/* Variables and functions */
 unsigned int BAYER_HEIGHT_ALIGN ; 
 unsigned int BAYER_WIDTH_ALIGN ; 
 unsigned int HEIGHT_ALIGN ; 
#define  V4L2_PIX_FMT_SBGGR8 131 
#define  V4L2_PIX_FMT_SGBRG8 130 
#define  V4L2_PIX_FMT_SGRBG8 129 
#define  V4L2_PIX_FMT_SRGGB8 128 
 unsigned int WIDTH_ALIGN ; 

__attribute__((used)) static void get_alignment(u32 fourcc,
			  unsigned int *walign, unsigned int *halign)
{
	switch (fourcc) {
	case V4L2_PIX_FMT_SBGGR8:
	case V4L2_PIX_FMT_SGBRG8:
	case V4L2_PIX_FMT_SGRBG8:
	case V4L2_PIX_FMT_SRGGB8:
		*walign = BAYER_WIDTH_ALIGN;
		*halign = BAYER_HEIGHT_ALIGN;
		return;
	default:
		*walign = WIDTH_ALIGN;
		*halign = HEIGHT_ALIGN;
		return;
	}
}