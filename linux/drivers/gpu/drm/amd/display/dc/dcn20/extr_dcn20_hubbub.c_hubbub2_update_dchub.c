#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hubbub {int dummy; } ;
struct dcn20_hubbub {int dummy; } ;
struct dchub_init_data {int fb_mode; int zfb_phys_addr_base; int zfb_mc_base_addr; int zfb_size_in_byte; int dchub_initialzied; int dchub_info_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_BASE ; 
 int /*<<< orphan*/  AGP_BOT ; 
 int /*<<< orphan*/  AGP_TOP ; 
 int /*<<< orphan*/  DCN_VM_AGP_BASE ; 
 int /*<<< orphan*/  DCN_VM_AGP_BOT ; 
 int /*<<< orphan*/  DCN_VM_AGP_TOP ; 
 int /*<<< orphan*/  DCN_VM_FB_LOCATION_BASE ; 
 int /*<<< orphan*/  DCN_VM_FB_LOCATION_TOP ; 
 int /*<<< orphan*/  FB_BASE ; 
 int /*<<< orphan*/  FB_TOP ; 
#define  FRAME_BUFFER_MODE_LOCAL_ONLY 130 
#define  FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL 129 
#define  FRAME_BUFFER_MODE_ZFB_ONLY 128 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_hubbub* TO_DCN20_HUBBUB (struct hubbub*) ; 

void hubbub2_update_dchub(struct hubbub *hubbub,
		struct dchub_init_data *dh_data)
{
	struct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	if (REG(DCN_VM_FB_LOCATION_TOP) == 0)
		return;

	switch (dh_data->fb_mode) {
	case FRAME_BUFFER_MODE_ZFB_ONLY:
		/*For ZFB case need to put DCHUB FB BASE and TOP upside down to indicate ZFB mode*/
		REG_UPDATE(DCN_VM_FB_LOCATION_TOP,
				FB_TOP, 0);

		REG_UPDATE(DCN_VM_FB_LOCATION_BASE,
				FB_BASE, 0xFFFFFF);

		/*This field defines the 24 MSBs, bits [47:24] of the 48 bit AGP Base*/
		REG_UPDATE(DCN_VM_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addr_base >> 24);

		/*This field defines the bottom range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addr >> 24);

		/*This field defines the top range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addr +
						dh_data->zfb_size_in_byte - 1) >> 24);
		break;
	case FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL:
		/*Should not touch FB LOCATION (done by VBIOS on AsicInit table)*/

		/*This field defines the 24 MSBs, bits [47:24] of the 48 bit AGP Base*/
		REG_UPDATE(DCN_VM_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addr_base >> 24);

		/*This field defines the bottom range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addr >> 24);

		/*This field defines the top range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addr +
						dh_data->zfb_size_in_byte - 1) >> 24);
		break;
	case FRAME_BUFFER_MODE_LOCAL_ONLY:
		/*Should not touch FB LOCATION (should be done by VBIOS)*/

		/*This field defines the 24 MSBs, bits [47:24] of the 48 bit AGP Base*/
		REG_UPDATE(DCN_VM_AGP_BASE,
				AGP_BASE, 0);

		/*This field defines the bottom range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_BOT,
				AGP_BOT, 0xFFFFFF);

		/*This field defines the top range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_TOP,
				AGP_TOP, 0);
		break;
	default:
		break;
	}

	dh_data->dchub_initialzied = true;
	dh_data->dchub_info_valid = false;
}