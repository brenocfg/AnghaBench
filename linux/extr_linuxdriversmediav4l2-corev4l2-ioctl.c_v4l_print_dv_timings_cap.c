#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  standards; int /*<<< orphan*/  max_pixelclock; int /*<<< orphan*/  min_pixelclock; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_dv_timings_cap {int type; TYPE_1__ bt; } ;

/* Variables and functions */
#define  V4L2_DV_BT_656_1120 128 
 int /*<<< orphan*/  pr_cont (char*,int,...) ; 

__attribute__((used)) static void v4l_print_dv_timings_cap(const void *arg, bool write_only)
{
	const struct v4l2_dv_timings_cap *p = arg;

	switch (p->type) {
	case V4L2_DV_BT_656_1120:
		pr_cont("type=bt-656/1120, width=%u-%u, height=%u-%u, pixelclock=%llu-%llu, standards=0x%x, capabilities=0x%x\n",
			p->bt.min_width, p->bt.max_width,
			p->bt.min_height, p->bt.max_height,
			p->bt.min_pixelclock, p->bt.max_pixelclock,
			p->bt.standards, p->bt.capabilities);
		break;
	default:
		pr_cont("type=%u\n", p->type);
		break;
	}
}