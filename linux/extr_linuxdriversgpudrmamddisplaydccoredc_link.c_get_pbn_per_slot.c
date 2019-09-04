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
typedef  int uint32_t ;
struct fixed31_32 {int dummy; } ;
struct dc_stream_state {TYPE_2__* sink; } ;
struct dc_link_settings {int link_rate; int lane_count; } ;
struct TYPE_4__ {TYPE_1__* link; } ;
struct TYPE_3__ {struct dc_link_settings cur_link_settings; } ;

/* Variables and functions */
 int LINK_RATE_REF_FREQ_IN_MHZ ; 
 struct fixed31_32 dc_fixpt_div_int (struct fixed31_32,int) ; 
 struct fixed31_32 dc_fixpt_from_int (int) ; 

__attribute__((used)) static struct fixed31_32 get_pbn_per_slot(struct dc_stream_state *stream)
{
	struct dc_link_settings *link_settings =
			&stream->sink->link->cur_link_settings;
	uint32_t link_rate_in_mbps =
			link_settings->link_rate * LINK_RATE_REF_FREQ_IN_MHZ;
	struct fixed31_32 mbps = dc_fixpt_from_int(
			link_rate_in_mbps * link_settings->lane_count);

	return dc_fixpt_div_int(mbps, 54);
}