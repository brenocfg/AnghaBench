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
struct TYPE_2__ {int /*<<< orphan*/  seeks; int /*<<< orphan*/  scan_objects; int /*<<< orphan*/  count_objects; } ;
struct panfrost_device {TYPE_1__ shrinker; } ;
struct drm_device {struct panfrost_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panfrost_gem_shrinker_count ; 
 int /*<<< orphan*/  panfrost_gem_shrinker_scan ; 
 int /*<<< orphan*/  register_shrinker (TYPE_1__*) ; 

void panfrost_gem_shrinker_init(struct drm_device *dev)
{
	struct panfrost_device *pfdev = dev->dev_private;
	pfdev->shrinker.count_objects = panfrost_gem_shrinker_count;
	pfdev->shrinker.scan_objects = panfrost_gem_shrinker_scan;
	pfdev->shrinker.seeks = DEFAULT_SEEKS;
	WARN_ON(register_shrinker(&pfdev->shrinker));
}