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
typedef  int uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; scalar_t__ smu_backend; } ;
struct iceland_smumgr {int /*<<< orphan*/ * power_tune_defaults; } ;
struct amdgpu_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
#define  DEVICE_ID_VI_ICELAND_M_6900 131 
#define  DEVICE_ID_VI_ICELAND_M_6901 130 
#define  DEVICE_ID_VI_ICELAND_M_6902 129 
#define  DEVICE_ID_VI_ICELAND_M_6903 128 
 int /*<<< orphan*/  defaults_iceland ; 
 int /*<<< orphan*/  defaults_icelandpro ; 
 int /*<<< orphan*/  defaults_icelandxt ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static void iceland_initialize_power_tune_defaults(struct pp_hwmgr *hwmgr)
{
	struct iceland_smumgr *smu_data = (struct iceland_smumgr *)(hwmgr->smu_backend);
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t dev_id;

	dev_id = adev->pdev->device;

	switch (dev_id) {
	case DEVICE_ID_VI_ICELAND_M_6900:
	case DEVICE_ID_VI_ICELAND_M_6903:
		smu_data->power_tune_defaults = &defaults_icelandxt;
		break;

	case DEVICE_ID_VI_ICELAND_M_6901:
	case DEVICE_ID_VI_ICELAND_M_6902:
		smu_data->power_tune_defaults = &defaults_icelandpro;
		break;
	default:
		smu_data->power_tune_defaults = &defaults_iceland;
		pr_warn("Unknown V.I. Device ID.\n");
		break;
	}
	return;
}