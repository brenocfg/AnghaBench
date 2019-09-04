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
struct v4l2_requestbuffers {scalar_t__ count; } ;
struct TYPE_2__ {scalar_t__ reqbufs_count; } ;
struct fimc_isp {TYPE_1__ video_capture; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FIMC_ISP_REQ_BUFS_MIN ; 
 int vb2_ioctl_reqbufs (struct file*,void*,struct v4l2_requestbuffers*) ; 
 struct fimc_isp* video_drvdata (struct file*) ; 

__attribute__((used)) static int isp_video_reqbufs(struct file *file, void *priv,
				struct v4l2_requestbuffers *rb)
{
	struct fimc_isp *isp = video_drvdata(file);
	int ret;

	ret = vb2_ioctl_reqbufs(file, priv, rb);
	if (ret < 0)
		return ret;

	if (rb->count && rb->count < FIMC_ISP_REQ_BUFS_MIN) {
		rb->count = 0;
		vb2_ioctl_reqbufs(file, priv, rb);
		ret = -ENOMEM;
	}

	isp->video_capture.reqbufs_count = rb->count;
	return ret;
}