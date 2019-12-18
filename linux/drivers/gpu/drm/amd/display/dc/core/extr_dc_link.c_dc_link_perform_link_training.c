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
struct dc_link_settings {int dummy; } ;
struct dc {int link_count; int /*<<< orphan*/ * links; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_link_dp_perform_link_training (int /*<<< orphan*/ ,struct dc_link_settings*,int) ; 

void dc_link_perform_link_training(struct dc *dc,
				   struct dc_link_settings *link_setting,
				   bool skip_video_pattern)
{
	int i;

	for (i = 0; i < dc->link_count; i++)
		dc_link_dp_perform_link_training(
			dc->links[i],
			link_setting,
			skip_video_pattern);
}