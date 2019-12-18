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
struct TYPE_5__ {int ucSpreadSpectrumType; int ucEnable; void* usSpreadSpectrumStep; void* usSpreadSpectrumAmount; void* usSpreadSpectrumAmountFrac; } ;
union atom_enable_ss {TYPE_2__ v3; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {unsigned int num_crtc; int /*<<< orphan*/  atom_context; TYPE_1__** crtcs; } ;
struct amdgpu_device {TYPE_3__ mode_info; } ;
struct amdgpu_atom_ss {scalar_t__ percentage; int type; int /*<<< orphan*/  step; int /*<<< orphan*/  amount; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_4__ {int pll_id; scalar_t__ enabled; } ;

/* Variables and functions */
#define  ATOM_DCPLL 131 
 int ATOM_EXTERNAL_SS_MASK ; 
#define  ATOM_PPLL1 130 
#define  ATOM_PPLL2 129 
#define  ATOM_PPLL_INVALID 128 
 int ATOM_PPLL_SS_TYPE_V3_DCPLL ; 
 int ATOM_PPLL_SS_TYPE_V3_P1PLL ; 
 int ATOM_PPLL_SS_TYPE_V3_P2PLL ; 
 int ATOM_SS_CENTRE_SPREAD_MODE_MASK ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  EnableSpreadSpectrumOnPPLL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union atom_enable_ss*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void amdgpu_atombios_crtc_program_ss(struct amdgpu_device *adev,
				     int enable,
				     int pll_id,
				     int crtc_id,
				     struct amdgpu_atom_ss *ss)
{
	unsigned i;
	int index = GetIndexIntoMasterTable(COMMAND, EnableSpreadSpectrumOnPPLL);
	union atom_enable_ss args;

	if (enable) {
		/* Don't mess with SS if percentage is 0 or external ss.
		 * SS is already disabled previously, and disabling it
		 * again can cause display problems if the pll is already
		 * programmed.
		 */
		if (ss->percentage == 0)
			return;
		if (ss->type & ATOM_EXTERNAL_SS_MASK)
			return;
	} else {
		for (i = 0; i < adev->mode_info.num_crtc; i++) {
			if (adev->mode_info.crtcs[i] &&
			    adev->mode_info.crtcs[i]->enabled &&
			    i != crtc_id &&
			    pll_id == adev->mode_info.crtcs[i]->pll_id) {
				/* one other crtc is using this pll don't turn
				 * off spread spectrum as it might turn off
				 * display on active crtc
				 */
				return;
			}
		}
	}

	memset(&args, 0, sizeof(args));

	args.v3.usSpreadSpectrumAmountFrac = cpu_to_le16(0);
	args.v3.ucSpreadSpectrumType = ss->type & ATOM_SS_CENTRE_SPREAD_MODE_MASK;
	switch (pll_id) {
	case ATOM_PPLL1:
		args.v3.ucSpreadSpectrumType |= ATOM_PPLL_SS_TYPE_V3_P1PLL;
		break;
	case ATOM_PPLL2:
		args.v3.ucSpreadSpectrumType |= ATOM_PPLL_SS_TYPE_V3_P2PLL;
		break;
	case ATOM_DCPLL:
		args.v3.ucSpreadSpectrumType |= ATOM_PPLL_SS_TYPE_V3_DCPLL;
		break;
	case ATOM_PPLL_INVALID:
		return;
	}
	args.v3.usSpreadSpectrumAmount = cpu_to_le16(ss->amount);
	args.v3.usSpreadSpectrumStep = cpu_to_le16(ss->step);
	args.v3.ucEnable = enable;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);
}