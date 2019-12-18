#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_3__ SCp; } ;
struct iscsi_task {int state; struct scsi_cmnd* sc; int /*<<< orphan*/  itt; struct iscsi_conn* conn; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
struct iscsi_session {TYPE_2__ cmdpool; TYPE_1__* tt; } ;
struct iscsi_conn {struct iscsi_task* login_task; struct iscsi_session* session; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cleanup_task ) (struct iscsi_task*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_SESSION (struct iscsi_session*,char*,int /*<<< orphan*/ ,int,struct scsi_cmnd*) ; 
 int ISCSI_TASK_FREE ; 
 int ISCSI_TASK_REQUEUE_SCSIQ ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_task*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_cmnd*) ; 

__attribute__((used)) static void iscsi_free_task(struct iscsi_task *task)
{
	struct iscsi_conn *conn = task->conn;
	struct iscsi_session *session = conn->session;
	struct scsi_cmnd *sc = task->sc;
	int oldstate = task->state;

	ISCSI_DBG_SESSION(session, "freeing task itt 0x%x state %d sc %p\n",
			  task->itt, task->state, task->sc);

	session->tt->cleanup_task(task);
	task->state = ISCSI_TASK_FREE;
	task->sc = NULL;
	/*
	 * login task is preallocated so do not free
	 */
	if (conn->login_task == task)
		return;

	kfifo_in(&session->cmdpool.queue, (void*)&task, sizeof(void*));

	if (sc) {
		/* SCSI eh reuses commands to verify us */
		sc->SCp.ptr = NULL;
		/*
		 * queue command may call this to free the task, so
		 * it will decide how to return sc to scsi-ml.
		 */
		if (oldstate != ISCSI_TASK_REQUEUE_SCSIQ)
			sc->scsi_done(sc);
	}
}