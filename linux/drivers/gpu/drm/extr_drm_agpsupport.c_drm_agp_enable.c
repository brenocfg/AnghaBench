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
struct drm_device {TYPE_1__* agp; } ;
struct drm_agp_mode {int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int enabled; int /*<<< orphan*/  bridge; int /*<<< orphan*/  mode; int /*<<< orphan*/  acquired; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  agp_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_agp_enable(struct drm_device *dev, struct drm_agp_mode mode)
{
	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;

	dev->agp->mode = mode.mode;
	agp_enable(dev->agp->bridge, mode.mode);
	dev->agp->enabled = 1;
	return 0;
}