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
 int EINVAL ; 

__attribute__((used)) static int flow_action_esp_replay_none(struct ib_flow_action_attrs_esp_replays *replay,
				       bool is_modify)
{
	/* This is used in order to modify an esp flow action with an enabled
	 * replay protection to a disabled one. This is only supported via
	 * modify, as in create verb we can simply drop the REPLAY attribute and
	 * achieve the same thing.
	 */
	return is_modify ? 0 : -EINVAL;
}