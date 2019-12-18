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
struct esp {TYPE_1__* target; int /*<<< orphan*/  esp_cmd_pool; int /*<<< orphan*/  active_cmds; int /*<<< orphan*/  queued_cmds; } ;
struct TYPE_2__ {scalar_t__ nego_goal_tags; scalar_t__ nego_goal_width; scalar_t__ nego_goal_offset; scalar_t__ nego_goal_period; scalar_t__ flags; } ;

/* Variables and functions */
 int ESP_MAX_TARGET ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esp_init_swstate(struct esp *esp)
{
	int i;

	INIT_LIST_HEAD(&esp->queued_cmds);
	INIT_LIST_HEAD(&esp->active_cmds);
	INIT_LIST_HEAD(&esp->esp_cmd_pool);

	/* Start with a clear state, domain validation (via ->slave_configure,
	 * spi_dv_device()) will attempt to enable SYNC, WIDE, and tagged
	 * commands.
	 */
	for (i = 0 ; i < ESP_MAX_TARGET; i++) {
		esp->target[i].flags = 0;
		esp->target[i].nego_goal_period = 0;
		esp->target[i].nego_goal_offset = 0;
		esp->target[i].nego_goal_width = 0;
		esp->target[i].nego_goal_tags = 0;
	}
}