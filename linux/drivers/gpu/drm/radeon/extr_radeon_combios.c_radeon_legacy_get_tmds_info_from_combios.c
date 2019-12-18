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
struct radeon_encoder_int_tmds {TYPE_2__* tmds_pll; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_4__ {void* value; void* freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBIOS_DFP_INFO_TABLE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 void* RBIOS16 (scalar_t__) ; 
 void* RBIOS32 (scalar_t__) ; 
 int RBIOS8 (scalar_t__) ; 
 scalar_t__ combios_get_table_offset (struct drm_device*,int /*<<< orphan*/ ) ; 

bool radeon_legacy_get_tmds_info_from_combios(struct radeon_encoder *encoder,
					      struct radeon_encoder_int_tmds *tmds)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	uint16_t tmds_info;
	int i, n;
	uint8_t ver;

	tmds_info = combios_get_table_offset(dev, COMBIOS_DFP_INFO_TABLE);

	if (tmds_info) {
		ver = RBIOS8(tmds_info);
		DRM_DEBUG_KMS("DFP table revision: %d\n", ver);
		if (ver == 3) {
			n = RBIOS8(tmds_info + 5) + 1;
			if (n > 4)
				n = 4;
			for (i = 0; i < n; i++) {
				tmds->tmds_pll[i].value =
				    RBIOS32(tmds_info + i * 10 + 0x08);
				tmds->tmds_pll[i].freq =
				    RBIOS16(tmds_info + i * 10 + 0x10);
				DRM_DEBUG_KMS("TMDS PLL From COMBIOS %u %x\n",
					  tmds->tmds_pll[i].freq,
					  tmds->tmds_pll[i].value);
			}
		} else if (ver == 4) {
			int stride = 0;
			n = RBIOS8(tmds_info + 5) + 1;
			if (n > 4)
				n = 4;
			for (i = 0; i < n; i++) {
				tmds->tmds_pll[i].value =
				    RBIOS32(tmds_info + stride + 0x08);
				tmds->tmds_pll[i].freq =
				    RBIOS16(tmds_info + stride + 0x10);
				if (i == 0)
					stride += 10;
				else
					stride += 6;
				DRM_DEBUG_KMS("TMDS PLL From COMBIOS %u %x\n",
					  tmds->tmds_pll[i].freq,
					  tmds->tmds_pll[i].value);
			}
		}
	} else {
		DRM_INFO("No TMDS info found in BIOS\n");
		return false;
	}
	return true;
}