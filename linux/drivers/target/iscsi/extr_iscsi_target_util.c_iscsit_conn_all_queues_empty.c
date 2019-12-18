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
struct iscsi_conn {int /*<<< orphan*/  response_queue_lock; int /*<<< orphan*/  response_queue_list; int /*<<< orphan*/  immed_queue_lock; int /*<<< orphan*/  immed_queue_list; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

bool iscsit_conn_all_queues_empty(struct iscsi_conn *conn)
{
	bool empty;

	spin_lock_bh(&conn->immed_queue_lock);
	empty = list_empty(&conn->immed_queue_list);
	spin_unlock_bh(&conn->immed_queue_lock);

	if (!empty)
		return empty;

	spin_lock_bh(&conn->response_queue_lock);
	empty = list_empty(&conn->response_queue_list);
	spin_unlock_bh(&conn->response_queue_lock);

	return empty;
}