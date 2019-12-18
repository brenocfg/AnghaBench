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
typedef  size_t u8 ;
struct ice_sched_node {size_t tc_num; } ;
struct ice_port_info {struct ice_sched_node*** sib_head; } ;

/* Variables and functions */

__attribute__((used)) static struct ice_sched_node *
ice_sched_get_first_node(struct ice_port_info *pi,
			 struct ice_sched_node *parent, u8 layer)
{
	return pi->sib_head[parent->tc_num][layer];
}