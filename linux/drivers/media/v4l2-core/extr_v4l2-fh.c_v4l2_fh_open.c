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
struct video_device {int dummy; } ;
struct v4l2_fh {int dummy; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct v4l2_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_add (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_init (struct v4l2_fh*,struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 

int v4l2_fh_open(struct file *filp)
{
	struct video_device *vdev = video_devdata(filp);
	struct v4l2_fh *fh = kzalloc(sizeof(*fh), GFP_KERNEL);

	filp->private_data = fh;
	if (fh == NULL)
		return -ENOMEM;
	v4l2_fh_init(fh, vdev);
	v4l2_fh_add(fh);
	return 0;
}