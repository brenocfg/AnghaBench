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
struct v4l2_pix_format {scalar_t__ pixelformat; int bytesperline; int height; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_NV16 ; 

__attribute__((used)) static u32 rvin_format_sizeimage(struct v4l2_pix_format *pix)
{
	if (pix->pixelformat == V4L2_PIX_FMT_NV16)
		return pix->bytesperline * pix->height * 2;

	return pix->bytesperline * pix->height;
}