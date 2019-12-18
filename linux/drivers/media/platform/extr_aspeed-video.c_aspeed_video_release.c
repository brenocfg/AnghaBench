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
struct file {int dummy; } ;
struct aspeed_video {int /*<<< orphan*/  video_lock; } ;

/* Variables and functions */
 int _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aspeed_video_stop (struct aspeed_video*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 struct aspeed_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int aspeed_video_release(struct file *file)
{
	int rc;
	struct aspeed_video *video = video_drvdata(file);

	mutex_lock(&video->video_lock);

	if (v4l2_fh_is_singular_file(file))
		aspeed_video_stop(video);

	rc = _vb2_fop_release(file, NULL);

	mutex_unlock(&video->video_lock);

	return rc;
}