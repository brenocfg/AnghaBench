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
struct stp_policy_node {unsigned int first_master; unsigned int last_master; unsigned int first_channel; unsigned int last_channel; } ;

/* Variables and functions */

void stp_policy_node_get_ranges(struct stp_policy_node *policy_node,
				unsigned int *mstart, unsigned int *mend,
				unsigned int *cstart, unsigned int *cend)
{
	*mstart	= policy_node->first_master;
	*mend	= policy_node->last_master;
	*cstart	= policy_node->first_channel;
	*cend	= policy_node->last_channel;
}