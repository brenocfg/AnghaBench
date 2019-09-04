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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  standards; int /*<<< orphan*/  il_vbackporch; int /*<<< orphan*/  il_vsync; int /*<<< orphan*/  il_vfrontporch; int /*<<< orphan*/  vbackporch; int /*<<< orphan*/  vsync; int /*<<< orphan*/  vfrontporch; int /*<<< orphan*/  hbackporch; int /*<<< orphan*/  hsync; int /*<<< orphan*/  hfrontporch; int /*<<< orphan*/  polarities; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelclock; int /*<<< orphan*/  interlaced; } ;
struct v4l2_dv_timings {int type; TYPE_1__ bt; } ;

/* Variables and functions */
#define  V4L2_DV_BT_656_1120 128 
 int /*<<< orphan*/  pr_cont (char*,int,...) ; 

__attribute__((used)) static void v4l_print_dv_timings(const void *arg, bool write_only)
{
	const struct v4l2_dv_timings *p = arg;

	switch (p->type) {
	case V4L2_DV_BT_656_1120:
		pr_cont("type=bt-656/1120, interlaced=%u, pixelclock=%llu, width=%u, height=%u, polarities=0x%x, hfrontporch=%u, hsync=%u, hbackporch=%u, vfrontporch=%u, vsync=%u, vbackporch=%u, il_vfrontporch=%u, il_vsync=%u, il_vbackporch=%u, standards=0x%x, flags=0x%x\n",
				p->bt.interlaced, p->bt.pixelclock,
				p->bt.width, p->bt.height,
				p->bt.polarities, p->bt.hfrontporch,
				p->bt.hsync, p->bt.hbackporch,
				p->bt.vfrontporch, p->bt.vsync,
				p->bt.vbackporch, p->bt.il_vfrontporch,
				p->bt.il_vsync, p->bt.il_vbackporch,
				p->bt.standards, p->bt.flags);
		break;
	default:
		pr_cont("type=%d\n", p->type);
		break;
	}
}