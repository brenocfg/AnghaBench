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
struct TYPE_2__ {int /*<<< orphan*/  edid; int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge_b850v3_lvds_dev_mutex ; 
 TYPE_1__* ge_b850v3_lvds_ptr ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ge_b850v3_lvds_remove(void)
{
	mutex_lock(&ge_b850v3_lvds_dev_mutex);
	/*
	 * This check is to avoid both the drivers
	 * removing the bridge in their remove() function
	 */
	if (!ge_b850v3_lvds_ptr)
		goto out;

	drm_bridge_remove(&ge_b850v3_lvds_ptr->bridge);

	kfree(ge_b850v3_lvds_ptr->edid);

	ge_b850v3_lvds_ptr = NULL;
out:
	mutex_unlock(&ge_b850v3_lvds_dev_mutex);
}