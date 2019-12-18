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
struct fimc_isp {TYPE_1__* pdev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fimc_vidioc_querycap (int /*<<< orphan*/ *,struct v4l2_capability*) ; 
 struct fimc_isp* video_drvdata (struct file*) ; 

__attribute__((used)) static int isp_video_querycap(struct file *file, void *priv,
					struct v4l2_capability *cap)
{
	struct fimc_isp *isp = video_drvdata(file);

	__fimc_vidioc_querycap(&isp->pdev->dev, cap);
	return 0;
}