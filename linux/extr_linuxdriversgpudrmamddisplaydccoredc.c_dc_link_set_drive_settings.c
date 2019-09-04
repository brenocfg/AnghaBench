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
struct link_training_settings {int dummy; } ;
struct dc_link {int dummy; } ;
struct dc {int link_count; struct dc_link const** links; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  dc_link_dp_set_drive_settings (struct dc_link const*,struct link_training_settings*) ; 

void dc_link_set_drive_settings(struct dc *dc,
				struct link_training_settings *lt_settings,
				const struct dc_link *link)
{

	int i;

	for (i = 0; i < dc->link_count; i++) {
		if (dc->links[i] == link)
			break;
	}

	if (i >= dc->link_count)
		ASSERT_CRITICAL(false);

	dc_link_dp_set_drive_settings(dc->links[i], lt_settings);
}