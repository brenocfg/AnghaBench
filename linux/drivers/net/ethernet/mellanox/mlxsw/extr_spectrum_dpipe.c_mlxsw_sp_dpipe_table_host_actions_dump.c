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
struct sk_buff {int dummy; } ;
struct devlink_dpipe_action {int /*<<< orphan*/  field_id; int /*<<< orphan*/ * header; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY ; 
 int /*<<< orphan*/  DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC ; 
 int devlink_dpipe_action_put (struct sk_buff*,struct devlink_dpipe_action*) ; 
 int /*<<< orphan*/  devlink_dpipe_header_ethernet ; 

__attribute__((used)) static int
mlxsw_sp_dpipe_table_host_actions_dump(void *priv, struct sk_buff *skb)
{
	struct devlink_dpipe_action action = {0};

	action.type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action.header = &devlink_dpipe_header_ethernet;
	action.field_id = DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC;

	return devlink_dpipe_action_put(skb, &action);
}