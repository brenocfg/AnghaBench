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
struct ib_flow_action_attrs_esp_replays {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int flow_action_esp_replay_def_ok(struct ib_flow_action_attrs_esp_replays *replay,
					 bool is_modify)
{
	/* Some replay protections could always be enabled without validating
	 * anything.
	 */
	return 0;
}