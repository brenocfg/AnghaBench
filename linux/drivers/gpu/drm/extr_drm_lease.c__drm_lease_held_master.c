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
struct drm_master {int /*<<< orphan*/  leases; scalar_t__ lessor; TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  idr_mutex; } ;
struct TYPE_4__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/ * idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _drm_lease_held_master(struct drm_master *master, int id)
{
	lockdep_assert_held(&master->dev->mode_config.idr_mutex);
	if (master->lessor)
		return idr_find(&master->leases, id) != NULL;
	return true;
}