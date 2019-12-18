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
struct dc_state {int stream_count; int /*<<< orphan*/ * streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_master_stream (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_multisync_trigger_params (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_enable_per_frame_crtc_master_sync(struct dc_state *context)
{
	int i = 0;

	if (context->stream_count < 2)
		return;
	for (i = 0; i < context->stream_count ; i++) {
		if (!context->streams[i])
			continue;
		/*
		 * TODO: add a function to read AMD VSDB bits and set
		 * crtc_sync_master.multi_sync_enabled flag
		 * For now it's set to false
		 */
		set_multisync_trigger_params(context->streams[i]);
	}
	set_master_stream(context->streams, context->stream_count);
}