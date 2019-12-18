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
struct TYPE_4__ {int num_ps; TYPE_3__* priv; TYPE_3__* ps; } ;
struct TYPE_5__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct TYPE_6__ {struct TYPE_6__* ps_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  r600_free_extended_power_table (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_cleanup_asic (struct radeon_device*) ; 

void trinity_dpm_fini(struct radeon_device *rdev)
{
	int i;

	trinity_cleanup_asic(rdev); /* ??? */

	for (i = 0; i < rdev->pm.dpm.num_ps; i++) {
		kfree(rdev->pm.dpm.ps[i].ps_priv);
	}
	kfree(rdev->pm.dpm.ps);
	kfree(rdev->pm.dpm.priv);
	r600_free_extended_power_table(rdev);
}