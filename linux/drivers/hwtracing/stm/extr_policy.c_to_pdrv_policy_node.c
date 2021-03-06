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
struct stp_policy_node {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 void* stp_policy_node_priv (struct stp_policy_node*) ; 
 struct stp_policy_node* to_stp_policy_node (struct config_item*) ; 

void *to_pdrv_policy_node(struct config_item *item)
{
	struct stp_policy_node *node = to_stp_policy_node(item);

	return stp_policy_node_priv(node);
}