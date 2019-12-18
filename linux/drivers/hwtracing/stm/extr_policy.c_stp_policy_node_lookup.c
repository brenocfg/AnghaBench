#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cg_item; } ;
struct stp_policy_node {TYPE_1__ group; } ;
struct stm_device {int /*<<< orphan*/  policy_mutex; scalar_t__ policy; } ;
struct TYPE_4__ {int /*<<< orphan*/  su_mutex; } ;

/* Variables and functions */
 struct stp_policy_node* __stp_policy_node_lookup (scalar_t__,char*) ; 
 int /*<<< orphan*/  config_item_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ stp_policy_subsys ; 

struct stp_policy_node *
stp_policy_node_lookup(struct stm_device *stm, char *s)
{
	struct stp_policy_node *policy_node = NULL;

	mutex_lock(&stp_policy_subsys.su_mutex);

	mutex_lock(&stm->policy_mutex);
	if (stm->policy)
		policy_node = __stp_policy_node_lookup(stm->policy, s);
	mutex_unlock(&stm->policy_mutex);

	if (policy_node)
		config_item_get(&policy_node->group.cg_item);
	else
		mutex_unlock(&stp_policy_subsys.su_mutex);

	return policy_node;
}