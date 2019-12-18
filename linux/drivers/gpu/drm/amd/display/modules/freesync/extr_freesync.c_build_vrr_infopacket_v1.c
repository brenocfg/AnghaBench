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
struct mod_vrr_params {int dummy; } ;
struct dc_info_packet {int valid; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
 int /*<<< orphan*/  build_vrr_infopacket_checksum (unsigned int*,struct dc_info_packet*) ; 
 int /*<<< orphan*/  build_vrr_infopacket_data (struct mod_vrr_params const*,struct dc_info_packet*) ; 
 int /*<<< orphan*/  build_vrr_infopacket_header_v1 (int,struct dc_info_packet*,unsigned int*) ; 

__attribute__((used)) static void build_vrr_infopacket_v1(enum signal_type signal,
		const struct mod_vrr_params *vrr,
		struct dc_info_packet *infopacket)
{
	/* SPD info packet for FreeSync */
	unsigned int payload_size = 0;

	build_vrr_infopacket_header_v1(signal, infopacket, &payload_size);
	build_vrr_infopacket_data(vrr, infopacket);
	build_vrr_infopacket_checksum(&payload_size, infopacket);

	infopacket->valid = true;
}