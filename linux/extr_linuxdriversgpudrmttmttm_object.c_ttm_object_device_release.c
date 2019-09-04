#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ttm_object_device {int /*<<< orphan*/  object_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_ht_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ttm_object_device*) ; 

void ttm_object_device_release(struct ttm_object_device **p_tdev)
{
	struct ttm_object_device *tdev = *p_tdev;

	*p_tdev = NULL;

	drm_ht_remove(&tdev->object_hash);

	kfree(tdev);
}