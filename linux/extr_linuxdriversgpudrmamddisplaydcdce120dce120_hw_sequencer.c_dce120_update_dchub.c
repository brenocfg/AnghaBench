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
struct dchub_init_data {int fb_mode; int zfb_phys_addr_base; int zfb_mc_base_addr; int zfb_size_in_byte; int dchub_initialzied; int dchub_info_valid; } ;
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_BASE ; 
 int /*<<< orphan*/  AGP_BOT ; 
 int /*<<< orphan*/  AGP_TOP ; 
 int /*<<< orphan*/  DCHUB_AGP_BASE ; 
 int /*<<< orphan*/  DCHUB_AGP_BOT ; 
 int /*<<< orphan*/  DCHUB_AGP_TOP ; 
 int /*<<< orphan*/  DCHUB_FB_LOCATION ; 
 int /*<<< orphan*/  FB_BASE ; 
 int /*<<< orphan*/  FB_TOP ; 
#define  FRAME_BUFFER_MODE_LOCAL_ONLY 130 
#define  FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL 129 
#define  FRAME_BUFFER_MODE_ZFB_ONLY 128 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dce120_update_dchub(
	struct dce_hwseq *hws,
	struct dchub_init_data *dh_data)
{
	/* TODO: port code from dal2 */
	switch (dh_data->fb_mode) {
	case FRAME_BUFFER_MODE_ZFB_ONLY:
		/*For ZFB case need to put DCHUB FB BASE and TOP upside down to indicate ZFB mode*/
		REG_UPDATE_2(DCHUB_FB_LOCATION,
				FB_TOP, 0,
				FB_BASE, 0x0FFFF);

		REG_UPDATE(DCHUB_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addr_base >> 22);

		REG_UPDATE(DCHUB_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addr >> 22);

		REG_UPDATE(DCHUB_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addr + dh_data->zfb_size_in_byte - 1) >> 22);
		break;
	case FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL:
		/*Should not touch FB LOCATION (done by VBIOS on AsicInit table)*/
		REG_UPDATE(DCHUB_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addr_base >> 22);

		REG_UPDATE(DCHUB_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addr >> 22);

		REG_UPDATE(DCHUB_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addr + dh_data->zfb_size_in_byte - 1) >> 22);
		break;
	case FRAME_BUFFER_MODE_LOCAL_ONLY:
		/*Should not touch FB LOCATION (done by VBIOS on AsicInit table)*/
		REG_UPDATE(DCHUB_AGP_BASE,
				AGP_BASE, 0);

		REG_UPDATE(DCHUB_AGP_BOT,
				AGP_BOT, 0x03FFFF);

		REG_UPDATE(DCHUB_AGP_TOP,
				AGP_TOP, 0);
		break;
	default:
		break;
	}

	dh_data->dchub_initialzied = true;
	dh_data->dchub_info_valid = false;
}