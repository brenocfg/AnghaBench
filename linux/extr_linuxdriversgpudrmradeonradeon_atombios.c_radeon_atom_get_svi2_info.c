#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union voltage_object_info {int /*<<< orphan*/  v3; } ;
struct TYPE_6__ {int ucSVDGpioId; int ucSVCGpioId; } ;
struct TYPE_7__ {TYPE_2__ asSVID2Obj; } ;
union voltage_object {TYPE_3__ v3; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {TYPE_4__* atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct TYPE_8__ {scalar_t__ bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOLTAGE_OBJ_SVID2 ; 
 int /*<<< orphan*/  VoltageObjectInfo ; 
 scalar_t__ atom_lookup_voltage_object_v3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ atom_parse_data_header (TYPE_4__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 

int radeon_atom_get_svi2_info(struct radeon_device *rdev,
			      u8 voltage_type,
			      u8 *svd_gpio_id, u8 *svc_gpio_id)
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
		case 3:
			switch (crev) {
			case 1:
				voltage_object = (union voltage_object *)
					atom_lookup_voltage_object_v3(&voltage_info->v3,
								      voltage_type,
								      VOLTAGE_OBJ_SVID2);
				if (voltage_object) {
					*svd_gpio_id = voltage_object->v3.asSVID2Obj.ucSVDGpioId;
					*svc_gpio_id = voltage_object->v3.asSVID2Obj.ucSVCGpioId;
				} else {
					return -EINVAL;
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
	return 0;
}