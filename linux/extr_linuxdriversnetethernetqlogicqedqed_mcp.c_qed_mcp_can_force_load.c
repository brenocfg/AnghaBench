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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum qed_override_force_load { ____Placeholder_qed_override_force_load } qed_override_force_load ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_ROLE_KDUMP ; 
 int /*<<< orphan*/  DRV_ROLE_OS ; 
 int /*<<< orphan*/  DRV_ROLE_PREBOOT ; 
#define  QED_OVERRIDE_FORCE_LOAD_ALWAYS 129 
#define  QED_OVERRIDE_FORCE_LOAD_NEVER 128 

__attribute__((used)) static bool
qed_mcp_can_force_load(u8 drv_role,
		       u8 exist_drv_role,
		       enum qed_override_force_load override_force_load)
{
	bool can_force_load = false;

	switch (override_force_load) {
	case QED_OVERRIDE_FORCE_LOAD_ALWAYS:
		can_force_load = true;
		break;
	case QED_OVERRIDE_FORCE_LOAD_NEVER:
		can_force_load = false;
		break;
	default:
		can_force_load = (drv_role == DRV_ROLE_OS &&
				  exist_drv_role == DRV_ROLE_PREBOOT) ||
				 (drv_role == DRV_ROLE_KDUMP &&
				  exist_drv_role == DRV_ROLE_OS);
		break;
	}

	return can_force_load;
}