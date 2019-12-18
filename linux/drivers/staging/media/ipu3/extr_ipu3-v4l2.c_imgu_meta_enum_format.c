#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fmtdesc {scalar_t__ type; scalar_t__ index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct imgu_video_device {TYPE_1__ vbq; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_META_OUTPUT ; 
 struct imgu_video_device* file_to_intel_imgu_node (struct file*) ; 
 TYPE_2__* meta_fmts ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int imgu_meta_enum_format(struct file *file, void *fh,
				 struct v4l2_fmtdesc *fmt)
{
	struct imgu_video_device *node = file_to_intel_imgu_node(file);
	unsigned int i = fmt->type == V4L2_BUF_TYPE_META_OUTPUT ? 0 : 1;

	/* Each node is dedicated to only one meta format */
	if (fmt->index > 0 || fmt->type != node->vbq.type)
		return -EINVAL;

	strscpy(fmt->description, meta_fmts[i].name, sizeof(fmt->description));
	fmt->pixelformat = meta_fmts[i].fourcc;

	return 0;
}