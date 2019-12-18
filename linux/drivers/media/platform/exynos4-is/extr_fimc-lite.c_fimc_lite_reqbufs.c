#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_requestbuffers {int /*<<< orphan*/  count; } ;
struct fimc_lite {int /*<<< orphan*/  reqbufs_count; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLITE_REQ_BUFS_MIN ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 
 int vb2_ioctl_reqbufs (struct file*,void*,struct v4l2_requestbuffers*) ; 
 struct fimc_lite* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_lite_reqbufs(struct file *file, void *priv,
			     struct v4l2_requestbuffers *reqbufs)
{
	struct fimc_lite *fimc = video_drvdata(file);
	int ret;

	reqbufs->count = max_t(u32, FLITE_REQ_BUFS_MIN, reqbufs->count);
	ret = vb2_ioctl_reqbufs(file, priv, reqbufs);
	if (!ret)
		fimc->reqbufs_count = reqbufs->count;

	return ret;
}