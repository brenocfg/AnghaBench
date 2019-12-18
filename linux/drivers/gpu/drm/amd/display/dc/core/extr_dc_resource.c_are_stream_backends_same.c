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
struct dc_stream_state {scalar_t__ dpms_off; } ;

/* Variables and functions */
 scalar_t__ is_hdr_static_meta_changed (struct dc_stream_state*,struct dc_stream_state*) ; 
 scalar_t__ is_timing_changed (struct dc_stream_state*,struct dc_stream_state*) ; 
 scalar_t__ is_vsc_info_packet_changed (struct dc_stream_state*,struct dc_stream_state*) ; 

__attribute__((used)) static bool are_stream_backends_same(
	struct dc_stream_state *stream_a, struct dc_stream_state *stream_b)
{
	if (stream_a == stream_b)
		return true;

	if (stream_a == NULL || stream_b == NULL)
		return false;

	if (is_timing_changed(stream_a, stream_b))
		return false;

	if (is_hdr_static_meta_changed(stream_a, stream_b))
		return false;

	if (stream_a->dpms_off != stream_b->dpms_off)
		return false;

	if (is_vsc_info_packet_changed(stream_a, stream_b))
		return false;

	return true;
}