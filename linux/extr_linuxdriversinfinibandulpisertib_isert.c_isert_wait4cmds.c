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
struct iscsi_conn {TYPE_1__* sess; } ;
struct TYPE_2__ {int /*<<< orphan*/  se_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  isert_info (char*,struct iscsi_conn*) ; 
 int /*<<< orphan*/  target_sess_cmd_list_set_waiting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_wait_for_sess_cmds (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isert_wait4cmds(struct iscsi_conn *conn)
{
	isert_info("iscsi_conn %p\n", conn);

	if (conn->sess) {
		target_sess_cmd_list_set_waiting(conn->sess->se_sess);
		target_wait_for_sess_cmds(conn->sess->se_sess);
	}
}