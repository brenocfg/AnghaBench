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
struct vivid_dev {int /*<<< orphan*/  sdr_buffersize; int /*<<< orphan*/  sdr_pixelformat; } ;
struct TYPE_3__ {int /*<<< orphan*/  reserved; int /*<<< orphan*/  buffersize; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ sdr; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vidioc_g_fmt_sdr_cap(struct file *file, void *fh, struct v4l2_format *f)
{
	struct vivid_dev *dev = video_drvdata(file);

	f->fmt.sdr.pixelformat = dev->sdr_pixelformat;
	f->fmt.sdr.buffersize = dev->sdr_buffersize;
	memset(f->fmt.sdr.reserved, 0, sizeof(f->fmt.sdr.reserved));
	return 0;
}