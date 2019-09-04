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
typedef  scalar_t__ uint64_t ;
struct iser_conn {scalar_t__ state; int /*<<< orphan*/  state_mutex; struct iscsi_conn* iscsi_conn; } ;
struct iscsi_endpoint {struct iser_conn* dd_data; } ;
struct iscsi_conn {struct iser_conn* dd_data; int /*<<< orphan*/  session; } ;
struct iscsi_cls_session {int dummy; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ISER_CONN_UP ; 
 int iscsi_conn_bind (struct iscsi_cls_session*,struct iscsi_cls_conn*,int) ; 
 struct iscsi_endpoint* iscsi_lookup_endpoint (scalar_t__) ; 
 int iser_alloc_rx_descriptors (struct iser_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_err (char*,...) ; 
 int /*<<< orphan*/  iser_info (char*,struct iscsi_conn*,struct iser_conn*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iscsi_iser_conn_bind(struct iscsi_cls_session *cls_session,
		     struct iscsi_cls_conn *cls_conn,
		     uint64_t transport_eph,
		     int is_leading)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iser_conn *iser_conn;
	struct iscsi_endpoint *ep;
	int error;

	error = iscsi_conn_bind(cls_session, cls_conn, is_leading);
	if (error)
		return error;

	/* the transport ep handle comes from user space so it must be
	 * verified against the global ib connections list */
	ep = iscsi_lookup_endpoint(transport_eph);
	if (!ep) {
		iser_err("can't bind eph %llx\n",
			 (unsigned long long)transport_eph);
		return -EINVAL;
	}
	iser_conn = ep->dd_data;

	mutex_lock(&iser_conn->state_mutex);
	if (iser_conn->state != ISER_CONN_UP) {
		error = -EINVAL;
		iser_err("iser_conn %p state is %d, teardown started\n",
			 iser_conn, iser_conn->state);
		goto out;
	}

	error = iser_alloc_rx_descriptors(iser_conn, conn->session);
	if (error)
		goto out;

	/* binds the iSER connection retrieved from the previously
	 * connected ep_handle to the iSCSI layer connection. exchanges
	 * connection pointers */
	iser_info("binding iscsi conn %p to iser_conn %p\n", conn, iser_conn);

	conn->dd_data = iser_conn;
	iser_conn->iscsi_conn = conn;

out:
	mutex_unlock(&iser_conn->state_mutex);
	return error;
}