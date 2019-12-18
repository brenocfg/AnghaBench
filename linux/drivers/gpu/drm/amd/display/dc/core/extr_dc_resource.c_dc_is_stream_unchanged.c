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
struct dc_stream_state {scalar_t__ ignore_msa_timing_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  are_stream_backends_same (struct dc_stream_state*,struct dc_stream_state*) ; 

bool dc_is_stream_unchanged(
	struct dc_stream_state *old_stream, struct dc_stream_state *stream)
{

	if (!are_stream_backends_same(old_stream, stream))
		return false;

	if (old_stream->ignore_msa_timing_param != stream->ignore_msa_timing_param)
		return false;

	return true;
}