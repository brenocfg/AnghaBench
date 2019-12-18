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
struct video_device {scalar_t__ vfl_dir; } ;
struct v4l2_framebuffer {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ VFL_DIR_RX ; 
 struct video_device* video_devdata (struct file*) ; 
 int vivid_vid_cap_s_fbuf (struct file*,void*,struct v4l2_framebuffer const*) ; 
 int vivid_vid_out_s_fbuf (struct file*,void*,struct v4l2_framebuffer const*) ; 

__attribute__((used)) static int vidioc_s_fbuf(struct file *file, void *fh, const struct v4l2_framebuffer *a)
{
	struct video_device *vdev = video_devdata(file);

	if (vdev->vfl_dir == VFL_DIR_RX)
		return vivid_vid_cap_s_fbuf(file, fh, a);
	return vivid_vid_out_s_fbuf(file, fh, a);
}