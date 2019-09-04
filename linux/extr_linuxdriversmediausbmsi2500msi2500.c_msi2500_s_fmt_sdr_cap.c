#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int dummy; } ;
struct TYPE_4__ {scalar_t__ pixelformat; int /*<<< orphan*/  buffersize; int /*<<< orphan*/  reserved; } ;
struct TYPE_5__ {TYPE_1__ sdr; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct msi2500_dev {int num_formats; scalar_t__ pixelformat; int /*<<< orphan*/  buffersize; int /*<<< orphan*/  dev; struct vb2_queue vb_queue; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ pixelformat; int /*<<< orphan*/  buffersize; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_3__* formats ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 
 struct msi2500_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int msi2500_s_fmt_sdr_cap(struct file *file, void *priv,
				 struct v4l2_format *f)
{
	struct msi2500_dev *dev = video_drvdata(file);
	struct vb2_queue *q = &dev->vb_queue;
	int i;

	dev_dbg(dev->dev, "pixelformat fourcc %4.4s\n",
		(char *)&f->fmt.sdr.pixelformat);

	if (vb2_is_busy(q))
		return -EBUSY;

	memset(f->fmt.sdr.reserved, 0, sizeof(f->fmt.sdr.reserved));
	for (i = 0; i < dev->num_formats; i++) {
		if (formats[i].pixelformat == f->fmt.sdr.pixelformat) {
			dev->pixelformat = formats[i].pixelformat;
			dev->buffersize = formats[i].buffersize;
			f->fmt.sdr.buffersize = formats[i].buffersize;
			return 0;
		}
	}

	dev->pixelformat = formats[0].pixelformat;
	dev->buffersize = formats[0].buffersize;
	f->fmt.sdr.pixelformat = formats[0].pixelformat;
	f->fmt.sdr.buffersize = formats[0].buffersize;

	return 0;
}