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
struct TYPE_10__ {int /*<<< orphan*/  susAccess; } ;
struct TYPE_15__ {TYPE_2__ usFirmwareCapability; int /*<<< orphan*/  usMaxPixelClock; int /*<<< orphan*/  ulDefaultMemoryClock; int /*<<< orphan*/  ulDefaultEngineClock; int /*<<< orphan*/  usMaxMemoryClockPLL_Input; int /*<<< orphan*/  usMinMemoryClockPLL_Input; int /*<<< orphan*/  ulMaxMemoryClockPLL_Output; int /*<<< orphan*/  usMinMemoryClockPLL_Output; int /*<<< orphan*/  usMaxEngineClockPLL_Input; int /*<<< orphan*/  usMinEngineClockPLL_Input; int /*<<< orphan*/  ulMaxEngineClockPLL_Output; int /*<<< orphan*/  usMinEngineClockPLL_Output; int /*<<< orphan*/  usMaxPixelClockPLL_Input; int /*<<< orphan*/  usMinPixelClockPLL_Input; int /*<<< orphan*/  ulMaxPixelClockPLL_Output; int /*<<< orphan*/  usReferenceClock; } ;
struct TYPE_9__ {int /*<<< orphan*/  usUniphyDPModeExtClkFreq; int /*<<< orphan*/  ulDefaultDispEngineClkFreq; int /*<<< orphan*/  usMemoryReferenceClock; int /*<<< orphan*/  usCoreReferenceClock; } ;
struct TYPE_14__ {int /*<<< orphan*/  usLcdMaxPixelClockPLL_Output; int /*<<< orphan*/  usLcdMinPixelClockPLL_Output; } ;
struct TYPE_13__ {int /*<<< orphan*/  ulMinPixelClockPLL_Output; } ;
union firmware_info {TYPE_7__ info; TYPE_1__ info_21; TYPE_6__ info_14; TYPE_5__ info_12; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct amdgpu_pll {int reference_freq; int pll_out_min; int pll_out_max; int lcd_pll_out_min; int lcd_pll_out_max; int pll_in_min; int pll_in_max; int min_post_div; int max_post_div; int max_frac_feedback_div; int min_ref_div; int max_ref_div; int min_feedback_div; int max_feedback_div; scalar_t__ best_vco; scalar_t__ reference_div; scalar_t__ min_frac_feedback_div; } ;
struct amdgpu_mode_info {int firmware_flags; TYPE_8__* atom_context; } ;
struct TYPE_12__ {int default_dispclk; int dp_extclk; int current_dispclk; int max_pixel_clock; void* default_mclk; void* default_sclk; struct amdgpu_pll* ppll; struct amdgpu_pll mpll; struct amdgpu_pll spll; } ;
struct TYPE_11__ {void* current_mclk; void* current_sclk; } ;
struct amdgpu_device {TYPE_4__ clock; TYPE_3__ pm; struct amdgpu_mode_info mode_info; } ;
struct TYPE_16__ {scalar_t__ bios; } ;

/* Variables and functions */
 int AMDGPU_MAX_PPLL ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FirmwareInfo ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_8__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

int amdgpu_atombios_get_clock_info(struct amdgpu_device *adev)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, FirmwareInfo);
	uint8_t frev, crev;
	uint16_t data_offset;
	int ret = -EINVAL;

	if (amdgpu_atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		int i;
		struct amdgpu_pll *ppll = &adev->clock.ppll[0];
		struct amdgpu_pll *spll = &adev->clock.spll;
		struct amdgpu_pll *mpll = &adev->clock.mpll;
		union firmware_info *firmware_info =
			(union firmware_info *)(mode_info->atom_context->bios +
						data_offset);
		/* pixel clocks */
		ppll->reference_freq =
		    le16_to_cpu(firmware_info->info.usReferenceClock);
		ppll->reference_div = 0;

		ppll->pll_out_min =
			le32_to_cpu(firmware_info->info_12.ulMinPixelClockPLL_Output);
		ppll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxPixelClockPLL_Output);

		ppll->lcd_pll_out_min =
			le16_to_cpu(firmware_info->info_14.usLcdMinPixelClockPLL_Output) * 100;
		if (ppll->lcd_pll_out_min == 0)
			ppll->lcd_pll_out_min = ppll->pll_out_min;
		ppll->lcd_pll_out_max =
			le16_to_cpu(firmware_info->info_14.usLcdMaxPixelClockPLL_Output) * 100;
		if (ppll->lcd_pll_out_max == 0)
			ppll->lcd_pll_out_max = ppll->pll_out_max;

		if (ppll->pll_out_min == 0)
			ppll->pll_out_min = 64800;

		ppll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinPixelClockPLL_Input);
		ppll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxPixelClockPLL_Input);

		ppll->min_post_div = 2;
		ppll->max_post_div = 0x7f;
		ppll->min_frac_feedback_div = 0;
		ppll->max_frac_feedback_div = 9;
		ppll->min_ref_div = 2;
		ppll->max_ref_div = 0x3ff;
		ppll->min_feedback_div = 4;
		ppll->max_feedback_div = 0xfff;
		ppll->best_vco = 0;

		for (i = 1; i < AMDGPU_MAX_PPLL; i++)
			adev->clock.ppll[i] = *ppll;

		/* system clock */
		spll->reference_freq =
			le16_to_cpu(firmware_info->info_21.usCoreReferenceClock);
		spll->reference_div = 0;

		spll->pll_out_min =
		    le16_to_cpu(firmware_info->info.usMinEngineClockPLL_Output);
		spll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxEngineClockPLL_Output);

		/* ??? */
		if (spll->pll_out_min == 0)
			spll->pll_out_min = 64800;

		spll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinEngineClockPLL_Input);
		spll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxEngineClockPLL_Input);

		spll->min_post_div = 1;
		spll->max_post_div = 1;
		spll->min_ref_div = 2;
		spll->max_ref_div = 0xff;
		spll->min_feedback_div = 4;
		spll->max_feedback_div = 0xff;
		spll->best_vco = 0;

		/* memory clock */
		mpll->reference_freq =
			le16_to_cpu(firmware_info->info_21.usMemoryReferenceClock);
		mpll->reference_div = 0;

		mpll->pll_out_min =
		    le16_to_cpu(firmware_info->info.usMinMemoryClockPLL_Output);
		mpll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxMemoryClockPLL_Output);

		/* ??? */
		if (mpll->pll_out_min == 0)
			mpll->pll_out_min = 64800;

		mpll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinMemoryClockPLL_Input);
		mpll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxMemoryClockPLL_Input);

		adev->clock.default_sclk =
		    le32_to_cpu(firmware_info->info.ulDefaultEngineClock);
		adev->clock.default_mclk =
		    le32_to_cpu(firmware_info->info.ulDefaultMemoryClock);

		mpll->min_post_div = 1;
		mpll->max_post_div = 1;
		mpll->min_ref_div = 2;
		mpll->max_ref_div = 0xff;
		mpll->min_feedback_div = 4;
		mpll->max_feedback_div = 0xff;
		mpll->best_vco = 0;

		/* disp clock */
		adev->clock.default_dispclk =
			le32_to_cpu(firmware_info->info_21.ulDefaultDispEngineClkFreq);
		/* set a reasonable default for DP */
		if (adev->clock.default_dispclk < 53900) {
			DRM_DEBUG("Changing default dispclk from %dMhz to 600Mhz\n",
				  adev->clock.default_dispclk / 100);
			adev->clock.default_dispclk = 60000;
		} else if (adev->clock.default_dispclk <= 60000) {
			DRM_DEBUG("Changing default dispclk from %dMhz to 625Mhz\n",
				  adev->clock.default_dispclk / 100);
			adev->clock.default_dispclk = 62500;
		}
		adev->clock.dp_extclk =
			le16_to_cpu(firmware_info->info_21.usUniphyDPModeExtClkFreq);
		adev->clock.current_dispclk = adev->clock.default_dispclk;

		adev->clock.max_pixel_clock = le16_to_cpu(firmware_info->info.usMaxPixelClock);
		if (adev->clock.max_pixel_clock == 0)
			adev->clock.max_pixel_clock = 40000;

		/* not technically a clock, but... */
		adev->mode_info.firmware_flags =
			le16_to_cpu(firmware_info->info.usFirmwareCapability.susAccess);

		ret = 0;
	}

	adev->pm.current_sclk = adev->clock.default_sclk;
	adev->pm.current_mclk = adev->clock.default_mclk;

	return ret;
}