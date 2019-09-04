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
struct pcm20 {int /*<<< orphan*/ * kthread; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_release (struct file*) ; 
 struct pcm20* video_drvdata (struct file*) ; 

__attribute__((used)) static int pcm20_release(struct file *file)
{
	struct pcm20 *dev = video_drvdata(file);

	if (v4l2_fh_is_singular_file(file) && !IS_ERR_OR_NULL(dev->kthread)) {
		kthread_stop(dev->kthread);
		dev->kthread = NULL;
	}
	return v4l2_fh_release(file);
}