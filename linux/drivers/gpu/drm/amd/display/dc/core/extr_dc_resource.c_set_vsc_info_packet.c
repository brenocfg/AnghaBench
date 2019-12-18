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
struct dc_info_packet {int /*<<< orphan*/  valid; } ;
struct dc_stream_state {struct dc_info_packet vsc_infopacket; } ;

/* Variables and functions */

__attribute__((used)) static void set_vsc_info_packet(
		struct dc_info_packet *info_packet,
		struct dc_stream_state *stream)
{
	if (!stream->vsc_infopacket.valid)
		return;

	*info_packet = stream->vsc_infopacket;
}