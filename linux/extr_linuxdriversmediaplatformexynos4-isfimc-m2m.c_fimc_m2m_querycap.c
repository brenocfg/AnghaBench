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
struct v4l2_capability {int dummy; } ;
struct fimc_dev {TYPE_1__* pdev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int V4L2_CAP_STREAMING ; 
 unsigned int V4L2_CAP_VIDEO_M2M_MPLANE ; 
 int /*<<< orphan*/  __fimc_vidioc_querycap (int /*<<< orphan*/ *,struct v4l2_capability*,unsigned int) ; 
 struct fimc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_m2m_querycap(struct file *file, void *fh,
				     struct v4l2_capability *cap)
{
	struct fimc_dev *fimc = video_drvdata(file);
	unsigned int caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M_MPLANE;

	__fimc_vidioc_querycap(&fimc->pdev->dev, cap, caps);
	return 0;
}