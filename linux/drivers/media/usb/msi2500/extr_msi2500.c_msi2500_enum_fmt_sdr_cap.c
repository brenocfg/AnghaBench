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
struct v4l2_fmtdesc {scalar_t__ index; int /*<<< orphan*/  pixelformat; } ;
struct msi2500_dev {scalar_t__ num_formats; int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_1__* formats ; 
 struct msi2500_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int msi2500_enum_fmt_sdr_cap(struct file *file, void *priv,
				    struct v4l2_fmtdesc *f)
{
	struct msi2500_dev *dev = video_drvdata(file);

	dev_dbg(dev->dev, "index=%d\n", f->index);

	if (f->index >= dev->num_formats)
		return -EINVAL;

	f->pixelformat = formats[f->index].pixelformat;

	return 0;
}