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
struct TYPE_2__ {scalar_t__ nr_deferred; } ;
struct panfrost_device {TYPE_1__ shrinker; } ;
struct drm_device {struct panfrost_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_shrinker (TYPE_1__*) ; 

void panfrost_gem_shrinker_cleanup(struct drm_device *dev)
{
	struct panfrost_device *pfdev = dev->dev_private;

	if (pfdev->shrinker.nr_deferred) {
		unregister_shrinker(&pfdev->shrinker);
	}
}