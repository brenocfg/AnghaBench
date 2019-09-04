#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dc_state {int stream_count; TYPE_1__** streams; } ;
struct dc_link {TYPE_2__* local_sink; } ;
struct dc {int link_count; struct dc_link** links; } ;
struct TYPE_4__ {scalar_t__ sink_signal; } ;
struct TYPE_3__ {scalar_t__ signal; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_TYPE_EDP ; 

__attribute__((used)) static struct dc_link *get_link_for_edp_not_in_use(
		struct dc *dc,
		struct dc_state *context)
{
	int i;
	struct dc_link *link = NULL;

	/* check if eDP panel is suppose to be set mode, if yes, no need to disable */
	for (i = 0; i < context->stream_count; i++) {
		if (context->streams[i]->signal == SIGNAL_TYPE_EDP)
			return NULL;
	}

	/* check if there is an eDP panel not in use */
	for (i = 0; i < dc->link_count; i++) {
		if (dc->links[i]->local_sink &&
			dc->links[i]->local_sink->sink_signal == SIGNAL_TYPE_EDP) {
			link = dc->links[i];
			break;
		}
	}

	return link;
}