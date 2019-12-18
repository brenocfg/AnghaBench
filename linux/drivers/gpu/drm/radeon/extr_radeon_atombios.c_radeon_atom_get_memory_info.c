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
struct TYPE_14__ {int ucNumOfVRAMModule; scalar_t__ aVramInfo; } ;
struct TYPE_13__ {int ucNumOfVRAMModule; scalar_t__ aVramInfo; } ;
struct TYPE_11__ {int ucNumOfVRAMModule; scalar_t__ aVramInfo; } ;
union vram_info {TYPE_5__ v2_1; TYPE_4__ v1_4; TYPE_2__ v1_3; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_10__ {TYPE_9__* atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct atom_memory_info {int mem_vendor; int mem_type; } ;
struct TYPE_18__ {scalar_t__ bios; } ;
struct TYPE_12__ {int ucMemoryVenderID; int ucMemoryType; } ;
struct TYPE_17__ {TYPE_3__ asMemory; int /*<<< orphan*/  usSize; } ;
struct TYPE_16__ {int ucMemoryVenderID; int ucMemoryType; int /*<<< orphan*/  usModuleSize; } ;
struct TYPE_15__ {int ucMemoryVenderID; int ucMemoryType; int /*<<< orphan*/  usModuleSize; } ;
typedef  TYPE_6__ ATOM_VRAM_MODULE_V7 ;
typedef  TYPE_7__ ATOM_VRAM_MODULE_V4 ;
typedef  TYPE_8__ ATOM_VRAM_MODULE_V3 ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VRAM_Info ; 
 scalar_t__ atom_parse_data_header (TYPE_9__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct atom_memory_info*,int /*<<< orphan*/ ,int) ; 

int radeon_atom_get_memory_info(struct radeon_device *rdev,
				u8 module_index, struct atom_memory_info *mem_info)
{
	int index = GetIndexIntoMasterTable(DATA, VRAM_Info);
	u8 frev, crev, i;
	u16 data_offset, size;
	union vram_info *vram_info;

	memset(mem_info, 0, sizeof(struct atom_memory_info));

	if (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) {
		vram_info = (union vram_info *)
			(rdev->mode_info.atom_context->bios + data_offset);
		switch (frev) {
		case 1:
			switch (crev) {
			case 3:
				/* r6xx */
				if (module_index < vram_info->v1_3.ucNumOfVRAMModule) {
					ATOM_VRAM_MODULE_V3 *vram_module =
						(ATOM_VRAM_MODULE_V3 *)vram_info->v1_3.aVramInfo;

					for (i = 0; i < module_index; i++) {
						if (le16_to_cpu(vram_module->usSize) == 0)
							return -EINVAL;
						vram_module = (ATOM_VRAM_MODULE_V3 *)
							((u8 *)vram_module + le16_to_cpu(vram_module->usSize));
					}
					mem_info->mem_vendor = vram_module->asMemory.ucMemoryVenderID & 0xf;
					mem_info->mem_type = vram_module->asMemory.ucMemoryType & 0xf0;
				} else
					return -EINVAL;
				break;
			case 4:
				/* r7xx, evergreen */
				if (module_index < vram_info->v1_4.ucNumOfVRAMModule) {
					ATOM_VRAM_MODULE_V4 *vram_module =
						(ATOM_VRAM_MODULE_V4 *)vram_info->v1_4.aVramInfo;

					for (i = 0; i < module_index; i++) {
						if (le16_to_cpu(vram_module->usModuleSize) == 0)
							return -EINVAL;
						vram_module = (ATOM_VRAM_MODULE_V4 *)
							((u8 *)vram_module + le16_to_cpu(vram_module->usModuleSize));
					}
					mem_info->mem_vendor = vram_module->ucMemoryVenderID & 0xf;
					mem_info->mem_type = vram_module->ucMemoryType & 0xf0;
				} else
					return -EINVAL;
				break;
			default:
				DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
				return -EINVAL;
			}
			break;
		case 2:
			switch (crev) {
			case 1:
				/* ni */
				if (module_index < vram_info->v2_1.ucNumOfVRAMModule) {
					ATOM_VRAM_MODULE_V7 *vram_module =
						(ATOM_VRAM_MODULE_V7 *)vram_info->v2_1.aVramInfo;

					for (i = 0; i < module_index; i++) {
						if (le16_to_cpu(vram_module->usModuleSize) == 0)
							return -EINVAL;
						vram_module = (ATOM_VRAM_MODULE_V7 *)
							((u8 *)vram_module + le16_to_cpu(vram_module->usModuleSize));
					}
					mem_info->mem_vendor = vram_module->ucMemoryVenderID & 0xf;
					mem_info->mem_type = vram_module->ucMemoryType & 0xf0;
				} else
					return -EINVAL;
				break;
			default:
				DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
				return -EINVAL;
			}
			break;
		default:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			return -EINVAL;
		}
		return 0;
	}
	return -EINVAL;
}