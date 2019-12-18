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
struct isert_np {int /*<<< orphan*/  mutex; } ;
struct isert_conn {int /*<<< orphan*/  release_work; int /*<<< orphan*/  node; TYPE_1__* cm_id; } ;
struct TYPE_2__ {struct isert_np* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  isert_put_conn (struct isert_conn*) ; 
 int /*<<< orphan*/  isert_release_wq ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isert_handle_unbound_conn(struct isert_conn *isert_conn)
{
	struct isert_np *isert_np = isert_conn->cm_id->context;

	mutex_lock(&isert_np->mutex);
	if (!list_empty(&isert_conn->node)) {
		/*
		 * This means iscsi doesn't know this connection
		 * so schedule a cleanup ourselves
		 */
		list_del_init(&isert_conn->node);
		isert_put_conn(isert_conn);
		queue_work(isert_release_wq, &isert_conn->release_work);
	}
	mutex_unlock(&isert_np->mutex);
}