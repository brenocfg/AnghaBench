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
struct dc {int link_count; struct dc_link** links; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_TYPE_EDP ; 

__attribute__((used)) static struct dc_link *get_link_for_edp(struct dc *dc)
{
	int i;

	for (i = 0; i < dc->link_count; i++) {
		if (dc->links[i]->connector_signal == SIGNAL_TYPE_EDP)
			return dc->links[i];
	}
	return NULL;
}