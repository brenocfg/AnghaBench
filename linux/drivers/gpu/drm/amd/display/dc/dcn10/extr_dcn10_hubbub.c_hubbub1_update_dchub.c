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
struct dcn10_hubbub {int dummy; } ;
struct dchub_init_data {int fb_mode; int zfb_phys_addr_base; int zfb_mc_base_addr; int zfb_size_in_byte; int dchub_initialzied; int dchub_info_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DCHUBBUB_SDPIF_AGP_BASE ; 
 int /*<<< orphan*/  DCHUBBUB_SDPIF_AGP_BOT ; 
 int /*<<< orphan*/  DCHUBBUB_SDPIF_AGP_TOP ; 
 int /*<<< orphan*/  DCHUBBUB_SDPIF_FB_BASE ; 
 int /*<<< orphan*/  DCHUBBUB_SDPIF_FB_TOP ; 
#define  FRAME_BUFFER_MODE_LOCAL_ONLY 130 
#define  FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL 129 
#define  FRAME_BUFFER_MODE_ZFB_ONLY 128 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDPIF_AGP_BASE ; 
 int /*<<< orphan*/  SDPIF_AGP_BOT ; 
 int /*<<< orphan*/  SDPIF_AGP_TOP ; 
 int /*<<< orphan*/  SDPIF_FB_BASE ; 
 int /*<<< orphan*/  SDPIF_FB_TOP ; 
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 

void hubbub1_update_dchub(
	struct hubbub *hubbub,
	struct dchub_init_data *dh_data)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	if (REG(DCHUBBUB_SDPIF_FB_TOP) == 0) {
		ASSERT(false);
		/*should not come here*/
		return;
	}
	/* TODO: port code from dal2 */
	switch (dh_data->fb_mode) {
	case FRAME_BUFFER_MODE_ZFB_ONLY:
		/*For ZFB case need to put DCHUB FB BASE and TOP upside down to indicate ZFB mode*/
		REG_UPDATE(DCHUBBUB_SDPIF_FB_TOP,
				SDPIF_FB_TOP, 0);

		REG_UPDATE(DCHUBBUB_SDPIF_FB_BASE,
				SDPIF_FB_BASE, 0x0FFFF);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BASE,
				SDPIF_AGP_BASE, dh_data->zfb_phys_addr_base >> 22);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BOT,
				SDPIF_AGP_BOT, dh_data->zfb_mc_base_addr >> 22);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_TOP,
				SDPIF_AGP_TOP, (dh_data->zfb_mc_base_addr +
						dh_data->zfb_size_in_byte - 1) >> 22);
		break;
	case FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL:
		/*Should not touch FB LOCATION (done by VBIOS on AsicInit table)*/

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BASE,
				SDPIF_AGP_BASE, dh_data->zfb_phys_addr_base >> 22);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BOT,
				SDPIF_AGP_BOT, dh_data->zfb_mc_base_addr >> 22);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_TOP,
				SDPIF_AGP_TOP, (dh_data->zfb_mc_base_addr +
						dh_data->zfb_size_in_byte - 1) >> 22);
		break;
	case FRAME_BUFFER_MODE_LOCAL_ONLY:
		/*Should not touch FB LOCATION (done by VBIOS on AsicInit table)*/
		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BASE,
				SDPIF_AGP_BASE, 0);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BOT,
				SDPIF_AGP_BOT, 0X03FFFF);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_TOP,
				SDPIF_AGP_TOP, 0);
		break;
	default:
		break;
	}

	dh_data->dchub_initialzied = true;
	dh_data->dchub_info_valid = false;
}