#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  usFbDiv; int /*<<< orphan*/  usFbDivFrac; } ;
struct atom_mpll_param {int vco_mode; int ucPllCntlFlag; int yclk_sel; int qdr; int half_rate; int /*<<< orphan*/  ucBWCntl; int /*<<< orphan*/  bwcntl; int /*<<< orphan*/  ucDllSpeed; int /*<<< orphan*/  dll_speed; int /*<<< orphan*/  ucPostDiv; int /*<<< orphan*/  post_div; TYPE_2__ ulFbDiv; void* clkf; void* clkfrac; int /*<<< orphan*/  ucInputFlag; int /*<<< orphan*/  ulClock; } ;
struct TYPE_3__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
typedef  int /*<<< orphan*/  args ;
typedef  struct atom_mpll_param COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_1 ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  ComputeMemoryClockParam ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MPLL_CNTL_FLAG_AD_HALF_RATE ; 
 int MPLL_CNTL_FLAG_BYPASS_DQ_PLL ; 
 int MPLL_CNTL_FLAG_QDR_ENABLE ; 
 int MPLL_CNTL_FLAG_VCO_MODE_MASK ; 
 int /*<<< orphan*/  MPLL_INPUT_FLAG_STROBE_MODE_EN ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct atom_mpll_param*,int /*<<< orphan*/ ,int) ; 

int amdgpu_atombios_get_memory_pll_dividers(struct amdgpu_device *adev,
					    u32 clock,
					    bool strobe_mode,
					    struct atom_mpll_param *mpll_param)
{
	COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_1 args;
	int index = GetIndexIntoMasterTable(COMMAND, ComputeMemoryClockParam);
	u8 frev, crev;

	memset(&args, 0, sizeof(args));
	memset(mpll_param, 0, sizeof(struct atom_mpll_param));

	if (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		return -EINVAL;

	switch (frev) {
	case 2:
		switch (crev) {
		case 1:
			/* SI */
			args.ulClock = cpu_to_le32(clock);	/* 10 khz */
			args.ucInputFlag = 0;
			if (strobe_mode)
				args.ucInputFlag |= MPLL_INPUT_FLAG_STROBE_MODE_EN;

			amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);

			mpll_param->clkfrac = le16_to_cpu(args.ulFbDiv.usFbDivFrac);
			mpll_param->clkf = le16_to_cpu(args.ulFbDiv.usFbDiv);
			mpll_param->post_div = args.ucPostDiv;
			mpll_param->dll_speed = args.ucDllSpeed;
			mpll_param->bwcntl = args.ucBWCntl;
			mpll_param->vco_mode =
				(args.ucPllCntlFlag & MPLL_CNTL_FLAG_VCO_MODE_MASK);
			mpll_param->yclk_sel =
				(args.ucPllCntlFlag & MPLL_CNTL_FLAG_BYPASS_DQ_PLL) ? 1 : 0;
			mpll_param->qdr =
				(args.ucPllCntlFlag & MPLL_CNTL_FLAG_QDR_ENABLE) ? 1 : 0;
			mpll_param->half_rate =
				(args.ucPllCntlFlag & MPLL_CNTL_FLAG_AD_HALF_RATE) ? 1 : 0;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}