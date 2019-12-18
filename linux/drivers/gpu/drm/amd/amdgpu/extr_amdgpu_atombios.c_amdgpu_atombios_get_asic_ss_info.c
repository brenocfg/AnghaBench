#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * asSpreadSpectrum; } ;
struct TYPE_10__ {int /*<<< orphan*/ * asSpreadSpectrum; } ;
struct TYPE_8__ {int /*<<< orphan*/ * asSpreadSpectrum; } ;
union asic_ss_info {TYPE_5__ info_3; TYPE_3__ info_2; TYPE_1__ info; } ;
struct TYPE_13__ {int ucClockIndication; int ucSpreadSpectrumMode; int /*<<< orphan*/  usSpreadRateIn10Hz; int /*<<< orphan*/  usSpreadSpectrumPercentage; int /*<<< orphan*/  ulTargetClockRange; } ;
struct TYPE_11__ {int ucClockIndication; int ucSpreadSpectrumMode; int /*<<< orphan*/  usSpreadRateIn10Hz; int /*<<< orphan*/  usSpreadSpectrumPercentage; int /*<<< orphan*/  ulTargetClockRange; } ;
struct TYPE_9__ {int ucClockIndication; int ucSpreadSpectrumMode; int /*<<< orphan*/  usSpreadRateInKhz; int /*<<< orphan*/  usSpreadSpectrumPercentage; int /*<<< orphan*/  ulTargetClockRange; } ;
union asic_ss_assignment {TYPE_6__ v3; TYPE_4__ v2; TYPE_2__ v1; } ;
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_mode_info {int firmware_flags; TYPE_7__* atom_context; } ;
struct amdgpu_device {int flags; struct amdgpu_mode_info mode_info; } ;
struct amdgpu_atom_ss {int type; int rate; int percentage_divider; void* percentage; } ;
struct TYPE_14__ {scalar_t__ bios; } ;
typedef  int /*<<< orphan*/  ATOM_COMMON_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ATOM_ASIC_SS_ASSIGNMENT_V3 ;
typedef  int /*<<< orphan*/  ATOM_ASIC_SS_ASSIGNMENT_V2 ;
typedef  int /*<<< orphan*/  ATOM_ASIC_SS_ASSIGNMENT ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int ASIC_INTERNAL_ENGINE_SS ; 
 int ASIC_INTERNAL_MEMORY_SS ; 
 int /*<<< orphan*/  ASIC_InternalSS_Info ; 
 int ATOM_BIOS_INFO_ENGINE_CLOCK_SS_SUPPORT ; 
 int ATOM_BIOS_INFO_MEMORY_CLOCK_SS_SUPPORT ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SS_MODE_V3_PERCENTAGE_DIV_BY_1000_MASK ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_7__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  amdgpu_atombios_get_igp_ss_overrides (struct amdgpu_device*,struct amdgpu_atom_ss*,int) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct amdgpu_atom_ss*,int /*<<< orphan*/ ,int) ; 

bool amdgpu_atombios_get_asic_ss_info(struct amdgpu_device *adev,
				      struct amdgpu_atom_ss *ss,
				      int id, u32 clock)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, ASIC_InternalSS_Info);
	uint16_t data_offset, size;
	union asic_ss_info *ss_info;
	union asic_ss_assignment *ss_assign;
	uint8_t frev, crev;
	int i, num_indices;

	if (id == ASIC_INTERNAL_MEMORY_SS) {
		if (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_MEMORY_CLOCK_SS_SUPPORT))
			return false;
	}
	if (id == ASIC_INTERNAL_ENGINE_SS) {
		if (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_ENGINE_CLOCK_SS_SUPPORT))
			return false;
	}

	memset(ss, 0, sizeof(struct amdgpu_atom_ss));
	if (amdgpu_atom_parse_data_header(mode_info->atom_context, index, &size,
				   &frev, &crev, &data_offset)) {

		ss_info =
			(union asic_ss_info *)(mode_info->atom_context->bios + data_offset);

		switch (frev) {
		case 1:
			num_indices = (size - sizeof(ATOM_COMMON_TABLE_HEADER)) /
				sizeof(ATOM_ASIC_SS_ASSIGNMENT);

			ss_assign = (union asic_ss_assignment *)((u8 *)&ss_info->info.asSpreadSpectrum[0]);
			for (i = 0; i < num_indices; i++) {
				if ((ss_assign->v1.ucClockIndication == id) &&
				    (clock <= le32_to_cpu(ss_assign->v1.ulTargetClockRange))) {
					ss->percentage =
						le16_to_cpu(ss_assign->v1.usSpreadSpectrumPercentage);
					ss->type = ss_assign->v1.ucSpreadSpectrumMode;
					ss->rate = le16_to_cpu(ss_assign->v1.usSpreadRateInKhz);
					ss->percentage_divider = 100;
					return true;
				}
				ss_assign = (union asic_ss_assignment *)
					((u8 *)ss_assign + sizeof(ATOM_ASIC_SS_ASSIGNMENT));
			}
			break;
		case 2:
			num_indices = (size - sizeof(ATOM_COMMON_TABLE_HEADER)) /
				sizeof(ATOM_ASIC_SS_ASSIGNMENT_V2);
			ss_assign = (union asic_ss_assignment *)((u8 *)&ss_info->info_2.asSpreadSpectrum[0]);
			for (i = 0; i < num_indices; i++) {
				if ((ss_assign->v2.ucClockIndication == id) &&
				    (clock <= le32_to_cpu(ss_assign->v2.ulTargetClockRange))) {
					ss->percentage =
						le16_to_cpu(ss_assign->v2.usSpreadSpectrumPercentage);
					ss->type = ss_assign->v2.ucSpreadSpectrumMode;
					ss->rate = le16_to_cpu(ss_assign->v2.usSpreadRateIn10Hz);
					ss->percentage_divider = 100;
					if ((crev == 2) &&
					    ((id == ASIC_INTERNAL_ENGINE_SS) ||
					     (id == ASIC_INTERNAL_MEMORY_SS)))
						ss->rate /= 100;
					return true;
				}
				ss_assign = (union asic_ss_assignment *)
					((u8 *)ss_assign + sizeof(ATOM_ASIC_SS_ASSIGNMENT_V2));
			}
			break;
		case 3:
			num_indices = (size - sizeof(ATOM_COMMON_TABLE_HEADER)) /
				sizeof(ATOM_ASIC_SS_ASSIGNMENT_V3);
			ss_assign = (union asic_ss_assignment *)((u8 *)&ss_info->info_3.asSpreadSpectrum[0]);
			for (i = 0; i < num_indices; i++) {
				if ((ss_assign->v3.ucClockIndication == id) &&
				    (clock <= le32_to_cpu(ss_assign->v3.ulTargetClockRange))) {
					ss->percentage =
						le16_to_cpu(ss_assign->v3.usSpreadSpectrumPercentage);
					ss->type = ss_assign->v3.ucSpreadSpectrumMode;
					ss->rate = le16_to_cpu(ss_assign->v3.usSpreadRateIn10Hz);
					if (ss_assign->v3.ucSpreadSpectrumMode &
					    SS_MODE_V3_PERCENTAGE_DIV_BY_1000_MASK)
						ss->percentage_divider = 1000;
					else
						ss->percentage_divider = 100;
					if ((id == ASIC_INTERNAL_ENGINE_SS) ||
					    (id == ASIC_INTERNAL_MEMORY_SS))
						ss->rate /= 100;
					if (adev->flags & AMD_IS_APU)
						amdgpu_atombios_get_igp_ss_overrides(adev, ss, id);
					return true;
				}
				ss_assign = (union asic_ss_assignment *)
					((u8 *)ss_assign + sizeof(ATOM_ASIC_SS_ASSIGNMENT_V3));
			}
			break;
		default:
			DRM_ERROR("Unsupported ASIC_InternalSS_Info table: %d %d\n", frev, crev);
			break;
		}

	}
	return false;
}