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
struct TYPE_3__ {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct vpbe_device {TYPE_1__ current_timings; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_cropcap {TYPE_2__ bounds; TYPE_2__ defrect; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int vpbe_g_cropcap(struct vpbe_device *vpbe_dev,
			  struct v4l2_cropcap *cropcap)
{
	if (!cropcap)
		return -EINVAL;
	cropcap->bounds.left = 0;
	cropcap->bounds.top = 0;
	cropcap->bounds.width = vpbe_dev->current_timings.xres;
	cropcap->bounds.height = vpbe_dev->current_timings.yres;
	cropcap->defrect = cropcap->bounds;

	return 0;
}