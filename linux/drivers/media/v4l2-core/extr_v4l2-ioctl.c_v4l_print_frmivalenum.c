#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct TYPE_8__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct TYPE_7__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct TYPE_10__ {TYPE_4__ step; TYPE_3__ max; TYPE_2__ min; } ;
struct TYPE_6__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct v4l2_frmivalenum {int pixel_format; int type; TYPE_5__ stepwise; TYPE_1__ discrete; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;

/* Variables and functions */
#define  V4L2_FRMIVAL_TYPE_CONTINUOUS 130 
#define  V4L2_FRMIVAL_TYPE_DISCRETE 129 
#define  V4L2_FRMIVAL_TYPE_STEPWISE 128 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void v4l_print_frmivalenum(const void *arg, bool write_only)
{
	const struct v4l2_frmivalenum *p = arg;

	pr_cont("index=%u, pixelformat=%c%c%c%c, wxh=%ux%u, type=%u",
			p->index,
			(p->pixel_format & 0xff),
			(p->pixel_format >>  8) & 0xff,
			(p->pixel_format >> 16) & 0xff,
			(p->pixel_format >> 24) & 0xff,
			p->width, p->height, p->type);
	switch (p->type) {
	case V4L2_FRMIVAL_TYPE_DISCRETE:
		pr_cont(", fps=%d/%d\n",
				p->discrete.numerator,
				p->discrete.denominator);
		break;
	case V4L2_FRMIVAL_TYPE_STEPWISE:
		pr_cont(", min=%d/%d, max=%d/%d, step=%d/%d\n",
				p->stepwise.min.numerator,
				p->stepwise.min.denominator,
				p->stepwise.max.numerator,
				p->stepwise.max.denominator,
				p->stepwise.step.numerator,
				p->stepwise.step.denominator);
		break;
	case V4L2_FRMIVAL_TYPE_CONTINUOUS:
		/* fall through */
	default:
		pr_cont("\n");
		break;
	}
}