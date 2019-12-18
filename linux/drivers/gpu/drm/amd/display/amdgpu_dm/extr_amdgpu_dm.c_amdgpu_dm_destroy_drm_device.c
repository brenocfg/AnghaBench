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
struct amdgpu_display_manager {int /*<<< orphan*/  atomic_obj; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_private_obj_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_dm_destroy_drm_device(struct amdgpu_display_manager *dm)
{
	drm_mode_config_cleanup(dm->ddev);
	drm_atomic_private_obj_fini(&dm->atomic_obj);
	return;
}