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
struct isert_conn {scalar_t__ logout_posted; struct iscsi_conn* conn; } ;
struct iscsi_conn {int /*<<< orphan*/  conn_logout_comp; } ;

/* Variables and functions */
 int HZ ; 
 int SECONDS_FOR_LOGOUT_COMP ; 
 int /*<<< orphan*/  isert_info (char*,struct isert_conn*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
isert_wait4logout(struct isert_conn *isert_conn)
{
	struct iscsi_conn *conn = isert_conn->conn;

	isert_info("conn %p\n", isert_conn);

	if (isert_conn->logout_posted) {
		isert_info("conn %p wait for conn_logout_comp\n", isert_conn);
		wait_for_completion_timeout(&conn->conn_logout_comp,
					    SECONDS_FOR_LOGOUT_COMP * HZ);
	}
}