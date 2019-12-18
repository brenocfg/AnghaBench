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
struct v4l2_requestbuffers {int dummy; } ;
struct iss_video_fh {int /*<<< orphan*/  queue; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct iss_video_fh* to_iss_video_fh (void*) ; 
 int vb2_reqbufs (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int
iss_video_reqbufs(struct file *file, void *fh, struct v4l2_requestbuffers *rb)
{
	struct iss_video_fh *vfh = to_iss_video_fh(fh);

	return vb2_reqbufs(&vfh->queue, rb);
}