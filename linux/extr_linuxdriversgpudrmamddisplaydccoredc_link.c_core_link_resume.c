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
struct dc_link {scalar_t__ connector_signal; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_TYPE_VIRTUAL ; 
 int /*<<< orphan*/  program_hpd_filter (struct dc_link*) ; 

void core_link_resume(struct dc_link *link)
{
	if (link->connector_signal != SIGNAL_TYPE_VIRTUAL)
		program_hpd_filter(link);
}