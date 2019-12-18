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
struct qed_hwfn {int dummy; } ;
typedef  enum qed_drv_role { ____Placeholder_qed_drv_role } qed_drv_role ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DRV_ROLE_KDUMP ; 
 int /*<<< orphan*/  DRV_ROLE_OS ; 
 int EINVAL ; 
#define  QED_DRV_ROLE_KDUMP 129 
#define  QED_DRV_ROLE_OS 128 

__attribute__((used)) static int eocre_get_mfw_drv_role(struct qed_hwfn *p_hwfn,
				  enum qed_drv_role drv_role,
				  u8 *p_mfw_drv_role)
{
	switch (drv_role) {
	case QED_DRV_ROLE_OS:
		*p_mfw_drv_role = DRV_ROLE_OS;
		break;
	case QED_DRV_ROLE_KDUMP:
		*p_mfw_drv_role = DRV_ROLE_KDUMP;
		break;
	default:
		DP_ERR(p_hwfn, "Unexpected driver role %d\n", drv_role);
		return -EINVAL;
	}

	return 0;
}