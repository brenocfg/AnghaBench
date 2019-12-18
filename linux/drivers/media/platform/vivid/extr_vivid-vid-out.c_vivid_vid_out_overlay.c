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
struct vivid_dev {unsigned int overlay_out_enabled; TYPE_1__* fmt_out; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  can_do_overlay; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (struct vivid_dev*,int,char*) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vivid_vid_out_overlay(struct file *file, void *fh, unsigned i)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (i && !dev->fmt_out->can_do_overlay) {
		dprintk(dev, 1, "unsupported output format for output overlay\n");
		return -EINVAL;
	}

	dev->overlay_out_enabled = i;
	return 0;
}