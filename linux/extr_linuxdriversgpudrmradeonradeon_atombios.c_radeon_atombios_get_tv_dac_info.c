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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct radeon_mode_info {TYPE_2__* atom_context; } ;
struct radeon_encoder_tv_dac {int ps2_tvdac_adj; int pal_tvdac_adj; int ntsc_tvdac_adj; int /*<<< orphan*/  tv_std; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct radeon_device {struct radeon_mode_info mode_info; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct _COMPASSIONATE_DATA {int ucDAC2_CRT2_BG_Adjustment; int ucDAC2_CRT2_DAC_Adjustment; int ucDAC2_PAL_BG_Adjustment; int ucDAC2_PAL_DAC_Adjustment; int ucDAC2_NTSC_BG_Adjustment; int ucDAC2_NTSC_DAC_Adjustment; } ;
struct TYPE_4__ {scalar_t__ bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CompassionateData ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atom_parse_data_header (TYPE_2__*,int,int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 struct radeon_encoder_tv_dac* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_get_tv_info (struct radeon_device*) ; 

struct radeon_encoder_tv_dac *
radeon_atombios_get_tv_dac_info(struct radeon_encoder *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, CompassionateData);
	uint16_t data_offset;
	struct _COMPASSIONATE_DATA *dac_info;
	uint8_t frev, crev;
	uint8_t bg, dac;
	struct radeon_encoder_tv_dac *tv_dac = NULL;

	if (atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {

		dac_info = (struct _COMPASSIONATE_DATA *)
			(mode_info->atom_context->bios + data_offset);

		tv_dac = kzalloc(sizeof(struct radeon_encoder_tv_dac), GFP_KERNEL);

		if (!tv_dac)
			return NULL;

		bg = dac_info->ucDAC2_CRT2_BG_Adjustment;
		dac = dac_info->ucDAC2_CRT2_DAC_Adjustment;
		tv_dac->ps2_tvdac_adj = (bg << 16) | (dac << 20);

		bg = dac_info->ucDAC2_PAL_BG_Adjustment;
		dac = dac_info->ucDAC2_PAL_DAC_Adjustment;
		tv_dac->pal_tvdac_adj = (bg << 16) | (dac << 20);

		bg = dac_info->ucDAC2_NTSC_BG_Adjustment;
		dac = dac_info->ucDAC2_NTSC_DAC_Adjustment;
		tv_dac->ntsc_tvdac_adj = (bg << 16) | (dac << 20);

		tv_dac->tv_std = radeon_atombios_get_tv_info(rdev);
	}
	return tv_dac;
}