#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_master {TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  lessee_idr; } ;
struct TYPE_4__ {int /*<<< orphan*/  idr_mutex; } ;
struct TYPE_5__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 TYPE_3__* drm_lease_owner (struct drm_master*) ; 
 struct drm_master* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_master*
_drm_find_lessee(struct drm_master *master, int lessee_id)
{
	lockdep_assert_held(&master->dev->mode_config.idr_mutex);
	return idr_find(&drm_lease_owner(master)->lessee_idr, lessee_id);
}