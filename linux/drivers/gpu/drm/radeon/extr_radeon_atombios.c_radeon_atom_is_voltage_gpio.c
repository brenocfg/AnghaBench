#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
union voltage_object_info {int /*<<< orphan*/  v3; int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; } ;
struct TYPE_10__ {int /*<<< orphan*/  ucVoltageControlId; } ;
struct TYPE_11__ {TYPE_4__ asControl; } ;
struct TYPE_8__ {int /*<<< orphan*/  ucVoltageControlId; } ;
struct TYPE_9__ {TYPE_2__ asControl; } ;
union voltage_object {TYPE_5__ v2; TYPE_3__ v1; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_7__ {TYPE_6__* atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct TYPE_12__ {scalar_t__ bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOLTAGE_CONTROLLED_BY_GPIO ; 
 int /*<<< orphan*/  VoltageObjectInfo ; 
 scalar_t__ atom_lookup_voltage_object_v1 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atom_lookup_voltage_object_v2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atom_lookup_voltage_object_v3 (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ atom_parse_data_header (TYPE_6__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 

bool
radeon_atom_is_voltage_gpio(struct radeon_device *rdev,
			    u8 voltage_type, u8 voltage_mode)
{
	int index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
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
				voltage_object = (union voltage_object *)
					atom_lookup_voltage_object_v1(&voltage_info->v1, voltage_type);
				if (voltage_object &&
				    (voltage_object->v1.asControl.ucVoltageControlId == VOLTAGE_CONTROLLED_BY_GPIO))
					return true;
				break;
			case 2:
				voltage_object = (union voltage_object *)
					atom_lookup_voltage_object_v2(&voltage_info->v2, voltage_type);
				if (voltage_object &&
				    (voltage_object->v2.asControl.ucVoltageControlId == VOLTAGE_CONTROLLED_BY_GPIO))
					return true;
				break;
			default:
				DRM_ERROR("unknown voltage object table\n");
				return false;
			}
			break;
		case 3:
			switch (crev) {
			case 1:
				if (atom_lookup_voltage_object_v3(&voltage_info->v3,
								  voltage_type, voltage_mode))
					return true;
				break;
			default:
				DRM_ERROR("unknown voltage object table\n");
				return false;
			}
			break;
		default:
			DRM_ERROR("unknown voltage object table\n");
			return false;
		}

	}
	return false;
}