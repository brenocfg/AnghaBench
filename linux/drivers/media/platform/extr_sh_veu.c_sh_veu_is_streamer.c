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
struct sh_veu_file {int dummy; } ;
struct sh_veu_dev {struct sh_veu_file* output; struct sh_veu_file* capture; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 

__attribute__((used)) static bool sh_veu_is_streamer(struct sh_veu_dev *veu, struct sh_veu_file *veu_file,
			       enum v4l2_buf_type type)
{
	return (type == V4L2_BUF_TYPE_VIDEO_CAPTURE &&
		veu_file == veu->capture) ||
		(type == V4L2_BUF_TYPE_VIDEO_OUTPUT &&
		 veu_file == veu->output);
}