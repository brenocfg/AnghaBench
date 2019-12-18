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
struct TYPE_11__ {int /*<<< orphan*/  ulGPUPLL_OutputFreq; } ;
struct TYPE_10__ {int /*<<< orphan*/  susAccess; } ;
struct TYPE_14__ {TYPE_2__ usFirmwareCapability; int /*<<< orphan*/  usMaxPixelClock; int /*<<< orphan*/  ulDefaultMemoryClock; int /*<<< orphan*/  ulDefaultEngineClock; int /*<<< orphan*/  usMaxMemoryClockPLL_Input; int /*<<< orphan*/  usMinMemoryClockPLL_Input; int /*<<< orphan*/  ulMaxMemoryClockPLL_Output; int /*<<< orphan*/  usMinMemoryClockPLL_Output; int /*<<< orphan*/  usReferenceClock; int /*<<< orphan*/  usMaxEngineClockPLL_Input; int /*<<< orphan*/  usMinEngineClockPLL_Input; int /*<<< orphan*/  ulMaxEngineClockPLL_Output; int /*<<< orphan*/  usMinEngineClockPLL_Output; int /*<<< orphan*/  usMaxPixelClockPLL_Input; int /*<<< orphan*/  usMinPixelClockPLL_Input; int /*<<< orphan*/  ulMaxPixelClockPLL_Output; int /*<<< orphan*/  usMinPixelClockPLL_Output; } ;
struct TYPE_9__ {int /*<<< orphan*/  usUniphyDPModeExtClkFreq; int /*<<< orphan*/  ulDefaultDispEngineClkFreq; int /*<<< orphan*/  usMemoryReferenceClock; int /*<<< orphan*/  usCoreReferenceClock; } ;
struct TYPE_15__ {int /*<<< orphan*/  usLcdMaxPixelClockPLL_Output; int /*<<< orphan*/  usLcdMinPixelClockPLL_Output; } ;
struct TYPE_13__ {int /*<<< orphan*/  ulMinPixelClockPLL_Output; } ;
union firmware_info {TYPE_3__ info_22; TYPE_6__ info; TYPE_1__ info_21; TYPE_7__ info_14; TYPE_5__ info_12; } ;
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct radeon_pll {int reference_freq; int pll_out_min; int pll_out_max; int lcd_pll_out_min; int lcd_pll_out_max; int pll_in_min; int pll_in_max; scalar_t__ reference_div; } ;
struct radeon_mode_info {int firmware_flags; TYPE_8__* atom_context; } ;
struct TYPE_12__ {int default_dispclk; int dp_extclk; int current_dispclk; int max_pixel_clock; int vco_freq; void* default_mclk; void* default_sclk; struct radeon_pll mpll; struct radeon_pll spll; struct radeon_pll dcpll; struct radeon_pll p2pll; struct radeon_pll p1pll; } ;
struct radeon_device {TYPE_4__ clock; struct radeon_mode_info mode_info; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_16__ {scalar_t__ bios; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE41 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE8 (struct radeon_device*) ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int /*<<< orphan*/  FirmwareInfo ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atom_parse_data_header (TYPE_8__*,int,int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_get_dentist_vco_freq (struct radeon_device*) ; 

bool radeon_atom_get_clock_info(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, FirmwareInfo);
	union firmware_info *firmware_info;
	uint8_t frev, crev;
	struct radeon_pll *p1pll = &rdev->clock.p1pll;
	struct radeon_pll *p2pll = &rdev->clock.p2pll;
	struct radeon_pll *dcpll = &rdev->clock.dcpll;
	struct radeon_pll *spll = &rdev->clock.spll;
	struct radeon_pll *mpll = &rdev->clock.mpll;
	uint16_t data_offset;

	if (atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		firmware_info =
			(union firmware_info *)(mode_info->atom_context->bios +
						data_offset);
		/* pixel clocks */
		p1pll->reference_freq =
		    le16_to_cpu(firmware_info->info.usReferenceClock);
		p1pll->reference_div = 0;

		if ((frev < 2) && (crev < 2))
			p1pll->pll_out_min =
				le16_to_cpu(firmware_info->info.usMinPixelClockPLL_Output);
		else
			p1pll->pll_out_min =
				le32_to_cpu(firmware_info->info_12.ulMinPixelClockPLL_Output);
		p1pll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxPixelClockPLL_Output);

		if (((frev < 2) && (crev >= 4)) || (frev >= 2)) {
			p1pll->lcd_pll_out_min =
				le16_to_cpu(firmware_info->info_14.usLcdMinPixelClockPLL_Output) * 100;
			if (p1pll->lcd_pll_out_min == 0)
				p1pll->lcd_pll_out_min = p1pll->pll_out_min;
			p1pll->lcd_pll_out_max =
				le16_to_cpu(firmware_info->info_14.usLcdMaxPixelClockPLL_Output) * 100;
			if (p1pll->lcd_pll_out_max == 0)
				p1pll->lcd_pll_out_max = p1pll->pll_out_max;
		} else {
			p1pll->lcd_pll_out_min = p1pll->pll_out_min;
			p1pll->lcd_pll_out_max = p1pll->pll_out_max;
		}

		if (p1pll->pll_out_min == 0) {
			if (ASIC_IS_AVIVO(rdev))
				p1pll->pll_out_min = 64800;
			else
				p1pll->pll_out_min = 20000;
		}

		p1pll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinPixelClockPLL_Input);
		p1pll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxPixelClockPLL_Input);

		*p2pll = *p1pll;

		/* system clock */
		if (ASIC_IS_DCE4(rdev))
			spll->reference_freq =
				le16_to_cpu(firmware_info->info_21.usCoreReferenceClock);
		else
			spll->reference_freq =
				le16_to_cpu(firmware_info->info.usReferenceClock);
		spll->reference_div = 0;

		spll->pll_out_min =
		    le16_to_cpu(firmware_info->info.usMinEngineClockPLL_Output);
		spll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxEngineClockPLL_Output);

		/* ??? */
		if (spll->pll_out_min == 0) {
			if (ASIC_IS_AVIVO(rdev))
				spll->pll_out_min = 64800;
			else
				spll->pll_out_min = 20000;
		}

		spll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinEngineClockPLL_Input);
		spll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxEngineClockPLL_Input);

		/* memory clock */
		if (ASIC_IS_DCE4(rdev))
			mpll->reference_freq =
				le16_to_cpu(firmware_info->info_21.usMemoryReferenceClock);
		else
			mpll->reference_freq =
				le16_to_cpu(firmware_info->info.usReferenceClock);
		mpll->reference_div = 0;

		mpll->pll_out_min =
		    le16_to_cpu(firmware_info->info.usMinMemoryClockPLL_Output);
		mpll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxMemoryClockPLL_Output);

		/* ??? */
		if (mpll->pll_out_min == 0) {
			if (ASIC_IS_AVIVO(rdev))
				mpll->pll_out_min = 64800;
			else
				mpll->pll_out_min = 20000;
		}

		mpll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinMemoryClockPLL_Input);
		mpll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxMemoryClockPLL_Input);

		rdev->clock.default_sclk =
		    le32_to_cpu(firmware_info->info.ulDefaultEngineClock);
		rdev->clock.default_mclk =
		    le32_to_cpu(firmware_info->info.ulDefaultMemoryClock);

		if (ASIC_IS_DCE4(rdev)) {
			rdev->clock.default_dispclk =
				le32_to_cpu(firmware_info->info_21.ulDefaultDispEngineClkFreq);
			if (rdev->clock.default_dispclk == 0) {
				if (ASIC_IS_DCE6(rdev))
					rdev->clock.default_dispclk = 60000; /* 600 Mhz */
				else if (ASIC_IS_DCE5(rdev))
					rdev->clock.default_dispclk = 54000; /* 540 Mhz */
				else
					rdev->clock.default_dispclk = 60000; /* 600 Mhz */
			}
			/* set a reasonable default for DP */
			if (ASIC_IS_DCE6(rdev) && (rdev->clock.default_dispclk < 53900)) {
				DRM_INFO("Changing default dispclk from %dMhz to 600Mhz\n",
					 rdev->clock.default_dispclk / 100);
				rdev->clock.default_dispclk = 60000;
			}
			rdev->clock.dp_extclk =
				le16_to_cpu(firmware_info->info_21.usUniphyDPModeExtClkFreq);
			rdev->clock.current_dispclk = rdev->clock.default_dispclk;
		}
		*dcpll = *p1pll;

		rdev->clock.max_pixel_clock = le16_to_cpu(firmware_info->info.usMaxPixelClock);
		if (rdev->clock.max_pixel_clock == 0)
			rdev->clock.max_pixel_clock = 40000;

		/* not technically a clock, but... */
		rdev->mode_info.firmware_flags =
			le16_to_cpu(firmware_info->info.usFirmwareCapability.susAccess);

		if (ASIC_IS_DCE8(rdev))
			rdev->clock.vco_freq =
				le32_to_cpu(firmware_info->info_22.ulGPUPLL_OutputFreq);
		else if (ASIC_IS_DCE5(rdev))
			rdev->clock.vco_freq = rdev->clock.current_dispclk;
		else if (ASIC_IS_DCE41(rdev))
			radeon_atombios_get_dentist_vco_freq(rdev);
		else
			rdev->clock.vco_freq = rdev->clock.current_dispclk;

		if (rdev->clock.vco_freq == 0)
			rdev->clock.vco_freq = 360000;	/* 3.6 GHz */

		return true;
	}

	return false;
}