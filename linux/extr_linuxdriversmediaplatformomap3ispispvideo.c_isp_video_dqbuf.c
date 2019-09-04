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
struct v4l2_buffer {int dummy; } ;
struct isp_video_fh {int /*<<< orphan*/  queue; } ;
struct isp_video {int /*<<< orphan*/  queue_lock; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isp_video_fh* to_isp_video_fh (void*) ; 
 int vb2_dqbuf (int /*<<< orphan*/ *,struct v4l2_buffer*,int) ; 
 struct isp_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
isp_video_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
	struct isp_video_fh *vfh = to_isp_video_fh(fh);
	struct isp_video *video = video_drvdata(file);
	int ret;

	mutex_lock(&video->queue_lock);
	ret = vb2_dqbuf(&vfh->queue, b, file->f_flags & O_NONBLOCK);
	mutex_unlock(&video->queue_lock);

	return ret;
}