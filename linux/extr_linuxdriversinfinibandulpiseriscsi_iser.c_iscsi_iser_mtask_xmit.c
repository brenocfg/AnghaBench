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
struct iscsi_task {int /*<<< orphan*/  itt; } ;
struct iscsi_conn {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iser_send_control (struct iscsi_conn*,struct iscsi_task*) ; 

__attribute__((used)) static int
iscsi_iser_mtask_xmit(struct iscsi_conn *conn, struct iscsi_task *task)
{
	int error = 0;

	iser_dbg("mtask xmit [cid %d itt 0x%x]\n", conn->id, task->itt);

	error = iser_send_control(conn, task);

	/* since iser xmits control with zero copy, tasks can not be recycled
	 * right after sending them.
	 * The recycling scheme is based on whether a response is expected
	 * - if yes, the task is recycled at iscsi_complete_pdu
	 * - if no,  the task is recycled at iser_snd_completion
	 */
	return error;
}