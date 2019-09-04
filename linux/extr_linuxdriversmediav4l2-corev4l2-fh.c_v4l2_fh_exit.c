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
struct v4l2_fh {int /*<<< orphan*/ * vdev; int /*<<< orphan*/  subscribe_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_event_unsubscribe_all (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l_disable_media_source (int /*<<< orphan*/ *) ; 

void v4l2_fh_exit(struct v4l2_fh *fh)
{
	if (fh->vdev == NULL)
		return;
	v4l_disable_media_source(fh->vdev);
	v4l2_event_unsubscribe_all(fh);
	mutex_destroy(&fh->subscribe_lock);
	fh->vdev = NULL;
}