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
struct isert_conn {int /*<<< orphan*/  release_work; int /*<<< orphan*/  qp; int /*<<< orphan*/  mutex; } ;
struct iscsi_conn {struct isert_conn* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_drain_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isert_conn_terminate (struct isert_conn*) ; 
 int /*<<< orphan*/  isert_info (char*,struct isert_conn*) ; 
 int /*<<< orphan*/  isert_put_unsol_pending_cmds (struct iscsi_conn*) ; 
 int /*<<< orphan*/  isert_release_wq ; 
 int /*<<< orphan*/  isert_wait4cmds (struct iscsi_conn*) ; 
 int /*<<< orphan*/  isert_wait4logout (struct isert_conn*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isert_wait_conn(struct iscsi_conn *conn)
{
	struct isert_conn *isert_conn = conn->context;

	isert_info("Starting conn %p\n", isert_conn);

	mutex_lock(&isert_conn->mutex);
	isert_conn_terminate(isert_conn);
	mutex_unlock(&isert_conn->mutex);

	ib_drain_qp(isert_conn->qp);
	isert_put_unsol_pending_cmds(conn);
	isert_wait4cmds(conn);
	isert_wait4logout(isert_conn);

	queue_work(isert_release_wq, &isert_conn->release_work);
}