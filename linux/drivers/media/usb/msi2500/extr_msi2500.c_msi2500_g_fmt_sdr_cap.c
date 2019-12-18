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
struct TYPE_3__ {int /*<<< orphan*/  reserved; int /*<<< orphan*/  buffersize; scalar_t__ pixelformat; } ;
struct TYPE_4__ {TYPE_1__ sdr; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct msi2500_dev {int /*<<< orphan*/  buffersize; scalar_t__ pixelformat; int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct msi2500_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int msi2500_g_fmt_sdr_cap(struct file *file, void *priv,
				 struct v4l2_format *f)
{
	struct msi2500_dev *dev = video_drvdata(file);

	dev_dbg(dev->dev, "pixelformat fourcc %4.4s\n",
		(char *)&dev->pixelformat);

	f->fmt.sdr.pixelformat = dev->pixelformat;
	f->fmt.sdr.buffersize = dev->buffersize;
	memset(f->fmt.sdr.reserved, 0, sizeof(f->fmt.sdr.reserved));

	return 0;
}