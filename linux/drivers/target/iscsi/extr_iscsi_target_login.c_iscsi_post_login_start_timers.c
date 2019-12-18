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
struct iscsi_session {TYPE_2__* sess_ops; } ;
struct iscsi_conn {TYPE_1__* conn_transport; struct iscsi_session* sess; } ;
struct TYPE_4__ {int /*<<< orphan*/  SessionType; } ;
struct TYPE_3__ {scalar_t__ transport_type; } ;

/* Variables and functions */
 scalar_t__ ISCSI_INFINIBAND ; 
 int /*<<< orphan*/  iscsit_start_nopin_timer (struct iscsi_conn*) ; 

__attribute__((used)) static void iscsi_post_login_start_timers(struct iscsi_conn *conn)
{
	struct iscsi_session *sess = conn->sess;
	/*
	 * FIXME: Unsolicited NopIN support for ISER
	 */
	if (conn->conn_transport->transport_type == ISCSI_INFINIBAND)
		return;

	if (!sess->sess_ops->SessionType)
		iscsit_start_nopin_timer(conn);
}