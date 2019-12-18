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
struct viu_fh {int /*<<< orphan*/  vb_vidq; } ;
struct v4l2_requestbuffers {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int videobuf_reqbufs (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int vidioc_reqbufs(struct file *file, void *priv,
				struct v4l2_requestbuffers *p)
{
	struct viu_fh *fh = priv;

	return videobuf_reqbufs(&fh->vb_vidq, p);
}