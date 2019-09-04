#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
union voltage_object_info {int /*<<< orphan*/  v3; int /*<<< orphan*/  v2; } ;
struct TYPE_17__ {int ucGpioEntryNum; int /*<<< orphan*/  ucPhaseDelay; int /*<<< orphan*/  ulGpioMaskVal; TYPE_5__* asVolGpioLut; } ;
struct TYPE_12__ {TYPE_8__ asGpioVoltageObj; } ;
struct TYPE_16__ {int ucNumOfVoltageEntries; TYPE_6__* asVIDAdjustEntries; } ;
struct TYPE_11__ {TYPE_7__ asFormula; } ;
union voltage_object {TYPE_3__ v3; TYPE_2__ v2; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_10__ {TYPE_9__* atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct atom_voltage_table {int count; int /*<<< orphan*/  phase_delay; void* mask_low; TYPE_4__* entries; } ;
struct TYPE_14__ {int /*<<< orphan*/  ulVoltageId; int /*<<< orphan*/  usVoltageValue; } ;
typedef  TYPE_5__ VOLTAGE_LUT_ENTRY_V2 ;
struct TYPE_15__ {int /*<<< orphan*/  usVoltageValue; } ;
typedef  TYPE_6__ VOLTAGE_LUT_ENTRY ;
struct TYPE_18__ {scalar_t__ bios; } ;
struct TYPE_13__ {void* smio_low; void* value; } ;
typedef  TYPE_7__ ATOM_VOLTAGE_FORMULA_V2 ;
typedef  TYPE_8__ ATOM_GPIO_VOLTAGE_OBJECT_V3 ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_VOLTAGE_ENTRIES ; 
 int /*<<< orphan*/  VoltageObjectInfo ; 
 scalar_t__ atom_lookup_voltage_object_v2 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atom_lookup_voltage_object_v3 (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ atom_parse_data_header (TYPE_9__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int radeon_atom_get_voltage_gpio_settings (struct radeon_device*,void*,int,void**,void**) ; 

int radeon_atom_get_voltage_table(struct radeon_device *rdev,
				  u8 voltage_type, u8 voltage_mode,
				  struct atom_voltage_table *voltage_table)
{
	int index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	int i, ret;
	union voltage_object_info *voltage_info;
	union voltage_object *voltage_object = NULL;

	if (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) {
		voltage_info = (union voltage_object_info *)
			(rdev->mode_info.atom_context->bios + data_offset);

		switch (frev) {
		case 1:
		case 2:
			switch (crev) {
			case 1:
				DRM_ERROR("old table version %d, %d\n", frev, crev);
				return -EINVAL;
			case 2:
				voltage_object = (union voltage_object *)
					atom_lookup_voltage_object_v2(&voltage_info->v2, voltage_type);
				if (voltage_object) {
					ATOM_VOLTAGE_FORMULA_V2 *formula =
						&voltage_object->v2.asFormula;
					VOLTAGE_LUT_ENTRY *lut;
					if (formula->ucNumOfVoltageEntries > MAX_VOLTAGE_ENTRIES)
						return -EINVAL;
					lut = &formula->asVIDAdjustEntries[0];
					for (i = 0; i < formula->ucNumOfVoltageEntries; i++) {
						voltage_table->entries[i].value =
							le16_to_cpu(lut->usVoltageValue);
						ret = radeon_atom_get_voltage_gpio_settings(rdev,
											    voltage_table->entries[i].value,
											    voltage_type,
											    &voltage_table->entries[i].smio_low,
											    &voltage_table->mask_low);
						if (ret)
							return ret;
						lut = (VOLTAGE_LUT_ENTRY *)
							((u8 *)lut + sizeof(VOLTAGE_LUT_ENTRY));
					}
					voltage_table->count = formula->ucNumOfVoltageEntries;
					return 0;
				}
				break;
			default:
				DRM_ERROR("unknown voltage object table\n");
				return -EINVAL;
			}
			break;
		case 3:
			switch (crev) {
			case 1:
				voltage_object = (union voltage_object *)
					atom_lookup_voltage_object_v3(&voltage_info->v3,
								      voltage_type, voltage_mode);
				if (voltage_object) {
					ATOM_GPIO_VOLTAGE_OBJECT_V3 *gpio =
						&voltage_object->v3.asGpioVoltageObj;
					VOLTAGE_LUT_ENTRY_V2 *lut;
					if (gpio->ucGpioEntryNum > MAX_VOLTAGE_ENTRIES)
						return -EINVAL;
					lut = &gpio->asVolGpioLut[0];
					for (i = 0; i < gpio->ucGpioEntryNum; i++) {
						voltage_table->entries[i].value =
							le16_to_cpu(lut->usVoltageValue);
						voltage_table->entries[i].smio_low =
							le32_to_cpu(lut->ulVoltageId);
						lut = (VOLTAGE_LUT_ENTRY_V2 *)
							((u8 *)lut + sizeof(VOLTAGE_LUT_ENTRY_V2));
					}
					voltage_table->mask_low = le32_to_cpu(gpio->ulGpioMaskVal);
					voltage_table->count = gpio->ucGpioEntryNum;
					voltage_table->phase_delay = gpio->ucPhaseDelay;
					return 0;
				}
				break;
			default:
				DRM_ERROR("unknown voltage object table\n");
				return -EINVAL;
			}
			break;
		default:
			DRM_ERROR("unknown voltage object table\n");
			return -EINVAL;
		}
	}
	return -EINVAL;
}