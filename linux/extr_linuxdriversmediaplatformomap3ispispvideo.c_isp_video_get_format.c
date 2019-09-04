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
struct v4l2_format {scalar_t__ type; } ;
struct isp_video_fh {struct v4l2_format format; } ;
struct isp_video {scalar_t__ type; int /*<<< orphan*/  mutex; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isp_video_fh* to_isp_video_fh (void*) ; 
 struct isp_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
isp_video_get_format(struct file *file, void *fh, struct v4l2_format *format)
{
	struct isp_video_fh *vfh = to_isp_video_fh(fh);
	struct isp_video *video = video_drvdata(file);

	if (format->type != video->type)
		return -EINVAL;

	mutex_lock(&video->mutex);
	*format = vfh->format;
	mutex_unlock(&video->mutex);

	return 0;
}