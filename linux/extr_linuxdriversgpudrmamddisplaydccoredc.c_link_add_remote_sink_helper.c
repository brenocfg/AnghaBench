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
struct dc_sink {int dummy; } ;
struct dc_link {size_t sink_count; struct dc_sink** remote_sinks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 size_t MAX_SINKS_PER_LINK ; 
 int /*<<< orphan*/  dc_sink_retain (struct dc_sink*) ; 

__attribute__((used)) static bool link_add_remote_sink_helper(struct dc_link *dc_link, struct dc_sink *sink)
{
	if (dc_link->sink_count >= MAX_SINKS_PER_LINK) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	dc_sink_retain(sink);

	dc_link->remote_sinks[dc_link->sink_count] = sink;
	dc_link->sink_count++;

	return true;
}