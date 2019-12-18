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
struct rect {int dummy; } ;
struct dc_stream_state {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

bool dc_is_stream_scaling_unchanged(
	struct dc_stream_state *old_stream, struct dc_stream_state *stream)
{
	if (old_stream == stream)
		return true;

	if (old_stream == NULL || stream == NULL)
		return false;

	if (memcmp(&old_stream->src,
			&stream->src,
			sizeof(struct rect)) != 0)
		return false;

	if (memcmp(&old_stream->dst,
			&stream->dst,
			sizeof(struct rect)) != 0)
		return false;

	return true;
}