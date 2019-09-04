#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ link_rate; } ;
struct dc_link {TYPE_1__ reported_link_cap; TYPE_1__ verified_link_cap; } ;

/* Variables and functions */
 scalar_t__ LINK_RATE_HIGH2 ; 
 scalar_t__ LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  retrieve_link_cap (struct dc_link*) ; 

void detect_edp_sink_caps(struct dc_link *link)
{
	retrieve_link_cap(link);

	if (link->reported_link_cap.link_rate == LINK_RATE_UNKNOWN)
		link->reported_link_cap.link_rate = LINK_RATE_HIGH2;

	link->verified_link_cap = link->reported_link_cap;
}