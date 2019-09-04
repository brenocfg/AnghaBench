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
struct stp_policy_node {int first_channel; int last_channel; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 struct stp_policy_node* to_stp_policy_node (struct config_item*) ; 

__attribute__((used)) static ssize_t
stp_policy_node_channels_show(struct config_item *item, char *page)
{
	struct stp_policy_node *policy_node = to_stp_policy_node(item);
	ssize_t count;

	count = sprintf(page, "%u %u\n", policy_node->first_channel,
			policy_node->last_channel);

	return count;
}