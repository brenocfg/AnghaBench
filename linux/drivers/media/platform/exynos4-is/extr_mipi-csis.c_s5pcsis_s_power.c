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
struct v4l2_subdev {int dummy; } ;
struct device {int dummy; } ;
struct csis_state {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int pm_runtime_get_sync (struct device*) ; 
 int pm_runtime_put_sync (struct device*) ; 
 struct csis_state* sd_to_csis_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5pcsis_s_power(struct v4l2_subdev *sd, int on)
{
	struct csis_state *state = sd_to_csis_state(sd);
	struct device *dev = &state->pdev->dev;

	if (on)
		return pm_runtime_get_sync(dev);

	return pm_runtime_put_sync(dev);
}