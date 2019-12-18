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
struct isp_video_fh {int /*<<< orphan*/  queue; } ;
struct isp_video {int /*<<< orphan*/  queue_lock; } ;
struct file {int /*<<< orphan*/  private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isp_video_fh* to_isp_video_fh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_poll (int /*<<< orphan*/ *,struct file*,int /*<<< orphan*/ *) ; 
 struct isp_video* video_drvdata (struct file*) ; 

__attribute__((used)) static __poll_t isp_video_poll(struct file *file, poll_table *wait)
{
	struct isp_video_fh *vfh = to_isp_video_fh(file->private_data);
	struct isp_video *video = video_drvdata(file);
	__poll_t ret;

	mutex_lock(&video->queue_lock);
	ret = vb2_poll(&vfh->queue, file, wait);
	mutex_unlock(&video->queue_lock);

	return ret;
}