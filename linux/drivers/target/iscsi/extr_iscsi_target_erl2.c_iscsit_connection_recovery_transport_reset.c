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
struct iscsi_conn {int /*<<< orphan*/  connection_recovery; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ iscsit_close_connection (struct iscsi_conn*) ; 

int iscsit_connection_recovery_transport_reset(struct iscsi_conn *conn)
{
	atomic_set(&conn->connection_recovery, 1);

	if (iscsit_close_connection(conn) < 0)
		return -1;

	return 0;
}