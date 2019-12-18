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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DSM_FUNC_ATSR ; 
 int /*<<< orphan*/  DMAR_DSM_FUNC_DRHD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dmar_check_one_atsr ; 
 int /*<<< orphan*/  dmar_hp_add_drhd ; 
 int /*<<< orphan*/  dmar_hp_release_drhd ; 
 int /*<<< orphan*/  dmar_hp_remove_drhd ; 
 int /*<<< orphan*/  dmar_release_one_atsr ; 
 int dmar_walk_dsm_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmar_hotplug_remove(acpi_handle handle)
{
	int ret;

	ret = dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_ATSR,
				     &dmar_check_one_atsr, NULL);
	if (ret)
		return ret;

	ret = dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
				     &dmar_hp_remove_drhd, NULL);
	if (ret == 0) {
		WARN_ON(dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_ATSR,
					       &dmar_release_one_atsr, NULL));
		WARN_ON(dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
					       &dmar_hp_release_drhd, NULL));
	} else {
		dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
				       &dmar_hp_add_drhd, NULL);
	}

	return ret;
}