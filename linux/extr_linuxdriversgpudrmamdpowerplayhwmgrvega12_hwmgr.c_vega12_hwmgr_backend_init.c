#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int min_fan_limit; int /*<<< orphan*/  min_performance_clock; int /*<<< orphan*/  target_temperature; int /*<<< orphan*/  target_fan_speed; } ;
struct vega12_hwmgr {int disable_dpm_mask; int workload_mask; int avfs_exist; int is_tlu_enabled; int gfxoff_controlled_by_driver; TYPE_5__ odn_fan_table; int /*<<< orphan*/  total_active_cus; scalar_t__ water_marks_bitmap; void* vddci_control; void* mvdd_control; void* vddc_control; } ;
struct TYPE_15__ {int ulMaxRPM; } ;
struct TYPE_14__ {int usFanPWMMinLimit; int /*<<< orphan*/  ulMinFanSCLKAcousticLimit; int /*<<< orphan*/  ucTargetTemperature; int /*<<< orphan*/  usMaxFanRPM; } ;
struct TYPE_16__ {TYPE_7__ fanInfo; TYPE_6__ advanceFanControlParameters; } ;
struct TYPE_9__ {int engineClock; int memoryClock; } ;
struct TYPE_10__ {int hardwarePerformanceLevels; int minimumClocksReductionPercentage; int vbiosInterruptId; TYPE_1__ clockStep; int /*<<< orphan*/  hardwareActivityPerformanceLevels; } ;
struct pp_hwmgr {int feature_mask; TYPE_8__ thermal_controller; TYPE_2__ platform_descriptor; struct vega12_hwmgr* backend; struct amdgpu_device* adev; } ;
struct TYPE_11__ {int /*<<< orphan*/  number; } ;
struct TYPE_12__ {TYPE_3__ cu_info; } ;
struct amdgpu_device {TYPE_4__ gfx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PP_GFXOFF_MASK ; 
 int /*<<< orphan*/  VEGA12_MAX_HARDWARE_POWERLEVELS ; 
 void* VEGA12_VOLTAGE_CONTROL_NONE ; 
 struct vega12_hwmgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega12_init_dpm_defaults (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  vega12_set_default_registry_data (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  vega12_set_features_platform_caps (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  vega12_set_private_data_based_on_pptable (struct pp_hwmgr*) ; 

__attribute__((used)) static int vega12_hwmgr_backend_init(struct pp_hwmgr *hwmgr)
{
	int result = 0;
	struct vega12_hwmgr *data;
	struct amdgpu_device *adev = hwmgr->adev;

	data = kzalloc(sizeof(struct vega12_hwmgr), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	hwmgr->backend = data;

	vega12_set_default_registry_data(hwmgr);

	data->disable_dpm_mask = 0xff;
	data->workload_mask = 0xff;

	/* need to set voltage control types before EVV patching */
	data->vddc_control = VEGA12_VOLTAGE_CONTROL_NONE;
	data->mvdd_control = VEGA12_VOLTAGE_CONTROL_NONE;
	data->vddci_control = VEGA12_VOLTAGE_CONTROL_NONE;

	data->water_marks_bitmap = 0;
	data->avfs_exist = false;

	vega12_set_features_platform_caps(hwmgr);

	vega12_init_dpm_defaults(hwmgr);

	/* Parse pptable data read from VBIOS */
	vega12_set_private_data_based_on_pptable(hwmgr);

	data->is_tlu_enabled = false;

	hwmgr->platform_descriptor.hardwareActivityPerformanceLevels =
			VEGA12_MAX_HARDWARE_POWERLEVELS;
	hwmgr->platform_descriptor.hardwarePerformanceLevels = 2;
	hwmgr->platform_descriptor.minimumClocksReductionPercentage = 50;

	hwmgr->platform_descriptor.vbiosInterruptId = 0x20000400; /* IRQ_SOURCE1_SW_INT */
	/* The true clock step depends on the frequency, typically 4.5 or 9 MHz. Here we use 5. */
	hwmgr->platform_descriptor.clockStep.engineClock = 500;
	hwmgr->platform_descriptor.clockStep.memoryClock = 500;

	data->total_active_cus = adev->gfx.cu_info.number;
	/* Setup default Overdrive Fan control settings */
	data->odn_fan_table.target_fan_speed =
			hwmgr->thermal_controller.advanceFanControlParameters.usMaxFanRPM;
	data->odn_fan_table.target_temperature =
			hwmgr->thermal_controller.advanceFanControlParameters.ucTargetTemperature;
	data->odn_fan_table.min_performance_clock =
			hwmgr->thermal_controller.advanceFanControlParameters.ulMinFanSCLKAcousticLimit;
	data->odn_fan_table.min_fan_limit =
			hwmgr->thermal_controller.advanceFanControlParameters.usFanPWMMinLimit *
			hwmgr->thermal_controller.fanInfo.ulMaxRPM / 100;

	if (hwmgr->feature_mask & PP_GFXOFF_MASK)
		data->gfxoff_controlled_by_driver = true;
	else
		data->gfxoff_controlled_by_driver = false;

	return result;
}