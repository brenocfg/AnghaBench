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
struct uvc_file_handle {int /*<<< orphan*/  vfh; int /*<<< orphan*/ * device; } ;
struct uvc_device {int /*<<< orphan*/  video; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct uvc_file_handle* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_function_connect (struct uvc_device*) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct uvc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int
uvc_v4l2_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct uvc_device *uvc = video_get_drvdata(vdev);
	struct uvc_file_handle *handle;

	handle = kzalloc(sizeof(*handle), GFP_KERNEL);
	if (handle == NULL)
		return -ENOMEM;

	v4l2_fh_init(&handle->vfh, vdev);
	v4l2_fh_add(&handle->vfh);

	handle->device = &uvc->video;
	file->private_data = &handle->vfh;

	uvc_function_connect(uvc);
	return 0;
}