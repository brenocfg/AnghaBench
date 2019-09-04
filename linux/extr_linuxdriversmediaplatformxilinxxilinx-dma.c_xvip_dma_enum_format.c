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
struct TYPE_3__ {int /*<<< orphan*/  pixelformat; } ;
struct xvip_dma {TYPE_2__* fmtinfo; TYPE_1__ format; } ;
struct v4l2_fmtdesc {scalar_t__ index; int /*<<< orphan*/  description; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  description; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct xvip_dma* to_xvip_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xvip_dma_enum_format(struct file *file, void *fh, struct v4l2_fmtdesc *f)
{
	struct v4l2_fh *vfh = file->private_data;
	struct xvip_dma *dma = to_xvip_dma(vfh->vdev);

	if (f->index > 0)
		return -EINVAL;

	f->pixelformat = dma->format.pixelformat;
	strlcpy(f->description, dma->fmtinfo->description,
		sizeof(f->description));

	return 0;
}