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
struct TYPE_4__ {int /*<<< orphan*/  su_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ stp_policy_subsys ; 

void stp_policy_node_put(struct stp_policy_node *policy_node)
{
	lockdep_assert_held(&stp_policy_subsys.su_mutex);

	mutex_unlock(&stp_policy_subsys.su_mutex);
	config_item_put(&policy_node->group.cg_item);
}