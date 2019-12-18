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
struct rdma_link_ops {int /*<<< orphan*/  list; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_ops ; 
 int /*<<< orphan*/  link_ops_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_ops_rwsem ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void rdma_link_register(struct rdma_link_ops *ops)
{
	down_write(&link_ops_rwsem);
	if (WARN_ON_ONCE(link_ops_get(ops->type)))
		goto out;
	list_add(&ops->list, &link_ops);
out:
	up_write(&link_ops_rwsem);
}