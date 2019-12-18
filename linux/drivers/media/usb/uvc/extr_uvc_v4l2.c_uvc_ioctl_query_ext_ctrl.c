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
struct v4l2_queryctrl {int /*<<< orphan*/  flags; int /*<<< orphan*/  default_value; int /*<<< orphan*/  step; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  id; int /*<<< orphan*/  member_0; } ;
struct v4l2_query_ext_ctrl {int elem_size; int elems; int /*<<< orphan*/  reserved; int /*<<< orphan*/  dims; scalar_t__ nr_of_dims; int /*<<< orphan*/  flags; int /*<<< orphan*/  default_value; int /*<<< orphan*/  step; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct uvc_video_chain {int dummy; } ;
struct uvc_fh {struct uvc_video_chain* chain; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int uvc_query_v4l2_ctrl (struct uvc_video_chain*,struct v4l2_queryctrl*) ; 

__attribute__((used)) static int uvc_ioctl_query_ext_ctrl(struct file *file, void *fh,
				    struct v4l2_query_ext_ctrl *qec)
{
	struct uvc_fh *handle = fh;
	struct uvc_video_chain *chain = handle->chain;
	struct v4l2_queryctrl qc = { qec->id };
	int ret;

	ret = uvc_query_v4l2_ctrl(chain, &qc);
	if (ret)
		return ret;

	qec->id = qc.id;
	qec->type = qc.type;
	strscpy(qec->name, qc.name, sizeof(qec->name));
	qec->minimum = qc.minimum;
	qec->maximum = qc.maximum;
	qec->step = qc.step;
	qec->default_value = qc.default_value;
	qec->flags = qc.flags;
	qec->elem_size = 4;
	qec->elems = 1;
	qec->nr_of_dims = 0;
	memset(qec->dims, 0, sizeof(qec->dims));
	memset(qec->reserved, 0, sizeof(qec->reserved));

	return 0;
}