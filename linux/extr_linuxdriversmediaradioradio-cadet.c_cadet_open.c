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
struct cadet {int /*<<< orphan*/  lock; int /*<<< orphan*/  read_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 struct cadet* video_drvdata (struct file*) ; 

__attribute__((used)) static int cadet_open(struct file *file)
{
	struct cadet *dev = video_drvdata(file);
	int err;

	mutex_lock(&dev->lock);
	err = v4l2_fh_open(file);
	if (err)
		goto fail;
	if (v4l2_fh_is_singular_file(file))
		init_waitqueue_head(&dev->read_queue);
fail:
	mutex_unlock(&dev->lock);
	return err;
}