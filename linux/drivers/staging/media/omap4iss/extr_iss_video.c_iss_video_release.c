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
struct v4l2_fh {int dummy; } ;
struct iss_video_fh {int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct iss_video {int /*<<< orphan*/  iss; TYPE_1__ video; int /*<<< orphan*/  type; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  iss_video_streamoff (struct file*,struct v4l2_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iss_video_fh*) ; 
 int /*<<< orphan*/  omap4iss_put (int /*<<< orphan*/ ) ; 
 struct iss_video_fh* to_iss_video_fh (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_del (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 
 struct iss_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int iss_video_release(struct file *file)
{
	struct iss_video *video = video_drvdata(file);
	struct v4l2_fh *vfh = file->private_data;
	struct iss_video_fh *handle = to_iss_video_fh(vfh);

	/* Disable streaming and free the buffers queue resources. */
	iss_video_streamoff(file, vfh, video->type);

	v4l2_pipeline_pm_use(&video->video.entity, 0);

	/* Release the videobuf2 queue */
	vb2_queue_release(&handle->queue);

	v4l2_fh_del(vfh);
	v4l2_fh_exit(vfh);
	kfree(handle);
	file->private_data = NULL;

	omap4iss_put(video->iss);

	return 0;
}