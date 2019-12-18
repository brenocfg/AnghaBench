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
struct mod_vrr_params {scalar_t__ state; int min_refresh_in_uhz; int max_refresh_in_uhz; } ;
struct dc_info_packet {int* sb; } ;

/* Variables and functions */
 scalar_t__ VRR_STATE_ACTIVE_FIXED ; 
 scalar_t__ VRR_STATE_ACTIVE_VARIABLE ; 
 scalar_t__ VRR_STATE_DISABLED ; 
 scalar_t__ VRR_STATE_UNSUPPORTED ; 

__attribute__((used)) static void build_vrr_infopacket_data(const struct mod_vrr_params *vrr,
		struct dc_info_packet *infopacket)
{
	/* PB1 = 0x1A (24bit AMD IEEE OUI (0x00001A) - Byte 0) */
	infopacket->sb[1] = 0x1A;

	/* PB2 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 1) */
	infopacket->sb[2] = 0x00;

	/* PB3 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 2) */
	infopacket->sb[3] = 0x00;

	/* PB4 = Reserved */

	/* PB5 = Reserved */

	/* PB6 = [Bits 7:3 = Reserved] */

	/* PB6 = [Bit 0 = FreeSync Supported] */
	if (vrr->state != VRR_STATE_UNSUPPORTED)
		infopacket->sb[6] |= 0x01;

	/* PB6 = [Bit 1 = FreeSync Enabled] */
	if (vrr->state != VRR_STATE_DISABLED &&
			vrr->state != VRR_STATE_UNSUPPORTED)
		infopacket->sb[6] |= 0x02;

	/* PB6 = [Bit 2 = FreeSync Active] */
	if (vrr->state == VRR_STATE_ACTIVE_VARIABLE ||
			vrr->state == VRR_STATE_ACTIVE_FIXED)
		infopacket->sb[6] |= 0x04;

	/* PB7 = FreeSync Minimum refresh rate (Hz) */
	infopacket->sb[7] = (unsigned char)(vrr->min_refresh_in_uhz / 1000000);

	/* PB8 = FreeSync Maximum refresh rate (Hz)
	 * Note: We should never go above the field rate of the mode timing set.
	 */
	infopacket->sb[8] = (unsigned char)(vrr->max_refresh_in_uhz / 1000000);


	//FreeSync HDR
	infopacket->sb[9] = 0;
	infopacket->sb[10] = 0;
}