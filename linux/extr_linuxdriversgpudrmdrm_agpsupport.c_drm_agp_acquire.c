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
struct drm_device {TYPE_1__* agp; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int acquired; int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  agp_backend_acquire (int /*<<< orphan*/ ) ; 

int drm_agp_acquire(struct drm_device *dev)
{
	if (!dev->agp)
		return -ENODEV;
	if (dev->agp->acquired)
		return -EBUSY;
	dev->agp->bridge = agp_backend_acquire(dev->pdev);
	if (!dev->agp->bridge)
		return -ENODEV;
	dev->agp->acquired = 1;
	return 0;
}