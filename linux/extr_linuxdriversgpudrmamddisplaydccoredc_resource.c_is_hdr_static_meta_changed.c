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
struct dc_stream_state {int /*<<< orphan*/  hdr_static_metadata; } ;
struct dc_info_packet {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool is_hdr_static_meta_changed(struct dc_stream_state *cur_stream,
	struct dc_stream_state *new_stream)
{
	if (cur_stream == NULL)
		return true;

	if (memcmp(&cur_stream->hdr_static_metadata,
			&new_stream->hdr_static_metadata,
			sizeof(struct dc_info_packet)) != 0)
		return true;

	return false;
}