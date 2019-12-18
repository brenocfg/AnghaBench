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
struct TYPE_5__ {void* ucPpll; int /*<<< orphan*/  ulDispEngClkFreq; } ;
struct TYPE_4__ {void* ucPpll; int /*<<< orphan*/  usPixelClock; int /*<<< orphan*/  ucCRTC; } ;
union set_pixel_clock {TYPE_2__ v6; TYPE_1__ v5; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_3__ mode_info; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE6 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE61 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE8 (struct radeon_device*) ; 
 int /*<<< orphan*/  ATOM_CRTC_INVALID ; 
 void* ATOM_DCPLL ; 
 void* ATOM_EXT_PLL1 ; 
 void* ATOM_PPLL0 ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixelClock ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union set_pixel_clock*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atombios_crtc_set_disp_eng_pll(struct radeon_device *rdev,
				    u32 dispclk)
{
	u8 frev, crev;
	int index;
	union set_pixel_clock args;

	memset(&args, 0, sizeof(args));

	index = GetIndexIntoMasterTable(COMMAND, SetPixelClock);
	if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev,
				   &crev))
		return;

	switch (frev) {
	case 1:
		switch (crev) {
		case 5:
			/* if the default dcpll clock is specified,
			 * SetPixelClock provides the dividers
			 */
			args.v5.ucCRTC = ATOM_CRTC_INVALID;
			args.v5.usPixelClock = cpu_to_le16(dispclk);
			args.v5.ucPpll = ATOM_DCPLL;
			break;
		case 6:
			/* if the default dcpll clock is specified,
			 * SetPixelClock provides the dividers
			 */
			args.v6.ulDispEngClkFreq = cpu_to_le32(dispclk);
			if (ASIC_IS_DCE61(rdev) || ASIC_IS_DCE8(rdev))
				args.v6.ucPpll = ATOM_EXT_PLL1;
			else if (ASIC_IS_DCE6(rdev))
				args.v6.ucPpll = ATOM_PPLL0;
			else
				args.v6.ucPpll = ATOM_DCPLL;
			break;
		default:
			DRM_ERROR("Unknown table version %d %d\n", frev, crev);
			return;
		}
		break;
	default:
		DRM_ERROR("Unknown table version %d %d\n", frev, crev);
		return;
	}
	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}