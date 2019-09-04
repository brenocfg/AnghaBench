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
struct vb2_queue {struct v4l2_fh* owner; } ;
struct v4l2_fh {scalar_t__ vdev; } ;

/* Variables and functions */
 int v4l_enable_media_source (scalar_t__) ; 

int v4l_vb2q_enable_media_source(struct vb2_queue *q)
{
	struct v4l2_fh *fh = q->owner;

	if (fh && fh->vdev)
		return v4l_enable_media_source(fh->vdev);
	return 0;
}