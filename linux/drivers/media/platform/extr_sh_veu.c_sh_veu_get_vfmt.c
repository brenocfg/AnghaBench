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
struct sh_veu_vfmt {int dummy; } ;
struct sh_veu_dev {struct sh_veu_vfmt vfmt_in; struct sh_veu_vfmt vfmt_out; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 128 

__attribute__((used)) static struct sh_veu_vfmt *sh_veu_get_vfmt(struct sh_veu_dev *veu,
					   enum v4l2_buf_type type)
{
	switch (type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		return &veu->vfmt_out;
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		return &veu->vfmt_in;
	default:
		return NULL;
	}
}