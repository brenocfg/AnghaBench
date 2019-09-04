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
struct rdma_id_private {struct rdma_bind_list* bind_list; } ;
struct TYPE_4__ {TYPE_1__* first; } ;
struct rdma_bind_list {TYPE_2__ owners; } ;
struct TYPE_3__ {scalar_t__ next; } ;

/* Variables and functions */
 int cma_check_port (struct rdma_bind_list*,struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_bind_listen(struct rdma_id_private *id_priv)
{
	struct rdma_bind_list *bind_list = id_priv->bind_list;
	int ret = 0;

	mutex_lock(&lock);
	if (bind_list->owners.first->next)
		ret = cma_check_port(bind_list, id_priv, 0);
	mutex_unlock(&lock);
	return ret;
}