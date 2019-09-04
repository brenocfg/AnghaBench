#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ucDCEClkType; int ucDCEClkSrc; int /*<<< orphan*/  ulDCEClkFreq; } ;
struct TYPE_6__ {TYPE_2__ asParam; } ;
union set_dce_clock {TYPE_3__ v2_1; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDCEClock ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union set_dce_clock*,int /*<<< orphan*/ ,int) ; 

u32 amdgpu_atombios_crtc_set_dce_clock(struct amdgpu_device *adev,
				       u32 freq, u8 clk_type, u8 clk_src)
{
	u8 frev, crev;
	int index;
	union set_dce_clock args;
	u32 ret_freq = 0;

	memset(&args, 0, sizeof(args));

	index = GetIndexIntoMasterTable(COMMAND, SetDCEClock);
	if (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev,
				   &crev))
		return 0;

	switch (frev) {
	case 2:
		switch (crev) {
		case 1:
			args.v2_1.asParam.ulDCEClkFreq = cpu_to_le32(freq); /* 10kHz units */
			args.v2_1.asParam.ucDCEClkType = clk_type;
			args.v2_1.asParam.ucDCEClkSrc = clk_src;
			amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);
			ret_freq = le32_to_cpu(args.v2_1.asParam.ulDCEClkFreq) * 10;
			break;
		default:
			DRM_ERROR("Unknown table version %d %d\n", frev, crev);
			return 0;
		}
		break;
	default:
		DRM_ERROR("Unknown table version %d %d\n", frev, crev);
		return 0;
	}

	return ret_freq;
}