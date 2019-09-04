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
typedef  size_t u8 ;
struct ice_sched_node {size_t tc_num; } ;
struct ice_port_info {TYPE_1__* root; } ;
struct TYPE_2__ {size_t num_children; struct ice_sched_node** children; } ;

/* Variables and functions */

struct ice_sched_node *ice_sched_get_tc_node(struct ice_port_info *pi, u8 tc)
{
	u8 i;

	if (!pi)
		return NULL;
	for (i = 0; i < pi->root->num_children; i++)
		if (pi->root->children[i]->tc_num == tc)
			return pi->root->children[i];
	return NULL;
}