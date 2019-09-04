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
struct xvip_video_format {int dummy; } ;
struct xvip_dma {struct xvip_video_format const* fmtinfo; int /*<<< orphan*/  format; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __xvip_dma_try_format (struct xvip_dma*,int /*<<< orphan*/ *,struct xvip_video_format const**) ; 
 struct xvip_dma* to_xvip_dma (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xvip_dma_set_format(struct file *file, void *fh, struct v4l2_format *format)
{
	struct v4l2_fh *vfh = file->private_data;
	struct xvip_dma *dma = to_xvip_dma(vfh->vdev);
	const struct xvip_video_format *info;

	__xvip_dma_try_format(dma, &format->fmt.pix, &info);

	if (vb2_is_busy(&dma->queue))
		return -EBUSY;

	dma->format = format->fmt.pix;
	dma->fmtinfo = info;

	return 0;
}