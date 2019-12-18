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
struct i40iw_cm_node {int /*<<< orphan*/  user_pri; int /*<<< orphan*/  rem_port; int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  loc_addr; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  ipv4; } ;
struct i40iw_cm_info {int /*<<< orphan*/  user_pri; int /*<<< orphan*/  rem_port; int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  loc_addr; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40iw_get_addr_info(struct i40iw_cm_node *cm_node,
				struct i40iw_cm_info *cm_info)
{
	cm_info->ipv4 = cm_node->ipv4;
	cm_info->vlan_id = cm_node->vlan_id;
	memcpy(cm_info->loc_addr, cm_node->loc_addr, sizeof(cm_info->loc_addr));
	memcpy(cm_info->rem_addr, cm_node->rem_addr, sizeof(cm_info->rem_addr));
	cm_info->loc_port = cm_node->loc_port;
	cm_info->rem_port = cm_node->rem_port;
	cm_info->user_pri = cm_node->user_pri;
}