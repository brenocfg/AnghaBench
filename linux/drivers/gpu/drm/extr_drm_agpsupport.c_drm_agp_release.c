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
struct TYPE_2__ {scalar_t__ acquired; int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  agp_backend_release (int /*<<< orphan*/ ) ; 

int drm_agp_release(struct drm_device *dev)
{
	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;
	agp_backend_release(dev->agp->bridge);
	dev->agp->acquired = 0;
	return 0;
}