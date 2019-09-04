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
struct ci_smumgr {int /*<<< orphan*/ * power_tune_defaults; } ;
struct amdgpu_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  defaults_bonaire_xt ; 
 int /*<<< orphan*/  defaults_hawaii_pro ; 
 int /*<<< orphan*/  defaults_hawaii_xt ; 
 int /*<<< orphan*/  defaults_saturn_xt ; 

__attribute__((used)) static void ci_initialize_power_tune_defaults(struct pp_hwmgr *hwmgr)
{
	struct ci_smumgr *smu_data = (struct ci_smumgr *)(hwmgr->smu_backend);
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t dev_id;

	dev_id = adev->pdev->device;

	switch (dev_id) {
	case 0x67BA:
	case 0x66B1:
		smu_data->power_tune_defaults = &defaults_hawaii_pro;
		break;
	case 0x67B8:
	case 0x66B0:
		smu_data->power_tune_defaults = &defaults_hawaii_xt;
		break;
	case 0x6640:
	case 0x6641:
	case 0x6646:
	case 0x6647:
		smu_data->power_tune_defaults = &defaults_saturn_xt;
		break;
	case 0x6649:
	case 0x6650:
	case 0x6651:
	case 0x6658:
	case 0x665C:
	case 0x665D:
	case 0x67A0:
	case 0x67A1:
	case 0x67A2:
	case 0x67A8:
	case 0x67A9:
	case 0x67AA:
	case 0x67B9:
	case 0x67BE:
	default:
		smu_data->power_tune_defaults = &defaults_bonaire_xt;
		break;
	}
}