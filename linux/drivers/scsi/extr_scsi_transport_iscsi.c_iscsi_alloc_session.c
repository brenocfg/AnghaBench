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
struct iscsi_transport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct iscsi_cls_session {int creator; int recovery_tmo; int recovery_tmo_sysfs_override; struct iscsi_cls_session* dd_data; TYPE_1__ dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  unbind_work; int /*<<< orphan*/  block_work; int /*<<< orphan*/  unblock_work; int /*<<< orphan*/  sess_list; int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  state; struct iscsi_transport* transport; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISCSI_DBG_TRANS_SESSION (struct iscsi_cls_session*,char*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_FREE ; 
 int /*<<< orphan*/  __iscsi_block_session ; 
 int /*<<< orphan*/  __iscsi_unbind_session ; 
 int /*<<< orphan*/  __iscsi_unblock_session ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  iscsi_scan_session ; 
 int /*<<< orphan*/  iscsi_session_release ; 
 struct iscsi_cls_session* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_get (struct Scsi_Host*) ; 
 int /*<<< orphan*/  session_recovery_timedout ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct iscsi_cls_session *
iscsi_alloc_session(struct Scsi_Host *shost, struct iscsi_transport *transport,
		    int dd_size)
{
	struct iscsi_cls_session *session;

	session = kzalloc(sizeof(*session) + dd_size,
			  GFP_KERNEL);
	if (!session)
		return NULL;

	session->transport = transport;
	session->creator = -1;
	session->recovery_tmo = 120;
	session->recovery_tmo_sysfs_override = false;
	session->state = ISCSI_SESSION_FREE;
	INIT_DELAYED_WORK(&session->recovery_work, session_recovery_timedout);
	INIT_LIST_HEAD(&session->sess_list);
	INIT_WORK(&session->unblock_work, __iscsi_unblock_session);
	INIT_WORK(&session->block_work, __iscsi_block_session);
	INIT_WORK(&session->unbind_work, __iscsi_unbind_session);
	INIT_WORK(&session->scan_work, iscsi_scan_session);
	spin_lock_init(&session->lock);

	/* this is released in the dev's release function */
	scsi_host_get(shost);
	session->dev.parent = &shost->shost_gendev;
	session->dev.release = iscsi_session_release;
	device_initialize(&session->dev);
	if (dd_size)
		session->dd_data = &session[1];

	ISCSI_DBG_TRANS_SESSION(session, "Completed session allocation\n");
	return session;
}