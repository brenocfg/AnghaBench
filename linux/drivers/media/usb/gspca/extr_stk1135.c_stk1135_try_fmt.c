#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; int bytesperline; int sizeimage; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 void* clamp (int,unsigned int,unsigned int) ; 

__attribute__((used)) static void stk1135_try_fmt(struct gspca_dev *gspca_dev, struct v4l2_format *fmt)
{
	fmt->fmt.pix.width = clamp(fmt->fmt.pix.width, 32U, 1280U);
	fmt->fmt.pix.height = clamp(fmt->fmt.pix.height, 32U, 1024U);
	/* round up to even numbers */
	fmt->fmt.pix.width += (fmt->fmt.pix.width & 1);
	fmt->fmt.pix.height += (fmt->fmt.pix.height & 1);

	fmt->fmt.pix.bytesperline = fmt->fmt.pix.width;
	fmt->fmt.pix.sizeimage = fmt->fmt.pix.width * fmt->fmt.pix.height;
}