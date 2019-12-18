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
struct iser_conn {int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  stop_completion; int /*<<< orphan*/ * iscsi_conn; } ;
struct iscsi_conn {struct iser_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_conn_stop (struct iscsi_cls_conn*,int) ; 
 int /*<<< orphan*/  iser_conn_terminate (struct iser_conn*) ; 
 int /*<<< orphan*/  iser_info (char*,struct iscsi_conn*,struct iser_conn*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unbind_iser_conn_mutex ; 

__attribute__((used)) static void
iscsi_iser_conn_stop(struct iscsi_cls_conn *cls_conn, int flag)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iser_conn *iser_conn = conn->dd_data;

	iser_info("stopping iscsi_conn: %p, iser_conn: %p\n", conn, iser_conn);

	/*
	 * Userspace may have goofed up and not bound the connection or
	 * might have only partially setup the connection.
	 */
	if (iser_conn) {
		mutex_lock(&iser_conn->state_mutex);
		mutex_lock(&unbind_iser_conn_mutex);
		iser_conn_terminate(iser_conn);
		iscsi_conn_stop(cls_conn, flag);

		/* unbind */
		iser_conn->iscsi_conn = NULL;
		conn->dd_data = NULL;
		mutex_unlock(&unbind_iser_conn_mutex);

		complete(&iser_conn->stop_completion);
		mutex_unlock(&iser_conn->state_mutex);
	} else {
		iscsi_conn_stop(cls_conn, flag);
	}
}