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
typedef  int u32 ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {int queue_depth; int /*<<< orphan*/  initiatorname; } ;
struct TYPE_2__ {int /*<<< orphan*/  fabric_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
target_set_nacl_queue_depth(struct se_portal_group *tpg,
			    struct se_node_acl *acl, u32 queue_depth)
{
	acl->queue_depth = queue_depth;

	if (!acl->queue_depth) {
		pr_warn("Queue depth for %s Initiator Node: %s is 0,"
			"defaulting to 1.\n", tpg->se_tpg_tfo->fabric_name,
			acl->initiatorname);
		acl->queue_depth = 1;
	}
}