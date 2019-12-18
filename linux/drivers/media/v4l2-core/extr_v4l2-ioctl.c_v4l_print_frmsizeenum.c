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
struct TYPE_4__ {int /*<<< orphan*/  step_height; int /*<<< orphan*/  step_width; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_frmsizeenum {int pixel_format; int type; TYPE_2__ stepwise; TYPE_1__ discrete; int /*<<< orphan*/  index; } ;

/* Variables and functions */
#define  V4L2_FRMSIZE_TYPE_CONTINUOUS 130 
#define  V4L2_FRMSIZE_TYPE_DISCRETE 129 
#define  V4L2_FRMSIZE_TYPE_STEPWISE 128 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void v4l_print_frmsizeenum(const void *arg, bool write_only)
{
	const struct v4l2_frmsizeenum *p = arg;

	pr_cont("index=%u, pixelformat=%c%c%c%c, type=%u",
			p->index,
			(p->pixel_format & 0xff),
			(p->pixel_format >>  8) & 0xff,
			(p->pixel_format >> 16) & 0xff,
			(p->pixel_format >> 24) & 0xff,
			p->type);
	switch (p->type) {
	case V4L2_FRMSIZE_TYPE_DISCRETE:
		pr_cont(", wxh=%ux%u\n",
			p->discrete.width, p->discrete.height);
		break;
	case V4L2_FRMSIZE_TYPE_STEPWISE:
		pr_cont(", min=%ux%u, max=%ux%u, step=%ux%u\n",
				p->stepwise.min_width,
				p->stepwise.min_height,
				p->stepwise.max_width,
				p->stepwise.max_height,
				p->stepwise.step_width,
				p->stepwise.step_height);
		break;
	case V4L2_FRMSIZE_TYPE_CONTINUOUS:
		/* fall through */
	default:
		pr_cont("\n");
		break;
	}
}