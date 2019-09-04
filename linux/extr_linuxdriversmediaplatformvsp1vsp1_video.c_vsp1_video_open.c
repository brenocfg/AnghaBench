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
struct vsp1_video {int /*<<< orphan*/  vsp1; int /*<<< orphan*/  video; } ;
struct v4l2_fh {int dummy; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct v4l2_fh*) ; 
 struct v4l2_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_add (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_del (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_init (struct v4l2_fh*,int /*<<< orphan*/ *) ; 
 struct vsp1_video* video_drvdata (struct file*) ; 
 int vsp1_device_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsp1_video_open(struct file *file)
{
	struct vsp1_video *video = video_drvdata(file);
	struct v4l2_fh *vfh;
	int ret = 0;

	vfh = kzalloc(sizeof(*vfh), GFP_KERNEL);
	if (vfh == NULL)
		return -ENOMEM;

	v4l2_fh_init(vfh, &video->video);
	v4l2_fh_add(vfh);

	file->private_data = vfh;

	ret = vsp1_device_get(video->vsp1);
	if (ret < 0) {
		v4l2_fh_del(vfh);
		v4l2_fh_exit(vfh);
		kfree(vfh);
	}

	return ret;
}