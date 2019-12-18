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
 int EBUSY ; 
 int EINVAL ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 128 

__attribute__((used)) static int sh_veu_stream_init(struct sh_veu_dev *veu, struct sh_veu_file *veu_file,
			      enum v4l2_buf_type type)
{
	struct sh_veu_file **stream;

	switch (type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		stream = &veu->capture;
		break;
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		stream = &veu->output;
		break;
	default:
		return -EINVAL;
	}

	if (*stream == veu_file)
		return 0;

	if (*stream)
		return -EBUSY;

	*stream = veu_file;

	return 0;
}