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
struct dc_info_packet {int valid; int* sb; } ;
typedef  enum color_transfer_func { ____Placeholder_color_transfer_func } color_transfer_func ;

/* Variables and functions */
 int TRANSFER_FUNC_GAMMA_22 ; 
 int TRANSFER_FUNC_UNKNOWN ; 

__attribute__((used)) static void build_vrr_infopacket_fs2_data(enum color_transfer_func app_tf,
		struct dc_info_packet *infopacket)
{
	if (app_tf != TRANSFER_FUNC_UNKNOWN) {
		infopacket->valid = true;

		infopacket->sb[6] |= 0x08;  // PB6 = [Bit 3 = Native Color Active]

		if (app_tf == TRANSFER_FUNC_GAMMA_22) {
			infopacket->sb[9] |= 0x04;  // PB6 = [Bit 2 = Gamma 2.2 EOTF Active]
		}
	}
}