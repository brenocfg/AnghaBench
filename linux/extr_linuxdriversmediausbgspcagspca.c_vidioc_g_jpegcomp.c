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
struct v4l2_jpegcompression {int dummy; } ;
struct gspca_dev {TYPE_1__* sd_desc; scalar_t__ usb_err; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* get_jcomp ) (struct gspca_dev*,struct v4l2_jpegcompression*) ;} ;

/* Variables and functions */
 int stub1 (struct gspca_dev*,struct v4l2_jpegcompression*) ; 
 struct gspca_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_jpegcomp(struct file *file, void *priv,
			struct v4l2_jpegcompression *jpegcomp)
{
	struct gspca_dev *gspca_dev = video_drvdata(file);

	gspca_dev->usb_err = 0;
	return gspca_dev->sd_desc->get_jcomp(gspca_dev, jpegcomp);
}