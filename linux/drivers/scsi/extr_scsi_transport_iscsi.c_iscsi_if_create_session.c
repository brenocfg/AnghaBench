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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  host_no; } ;
struct TYPE_4__ {TYPE_1__ c_session_ret; } ;
struct iscsi_uevent {TYPE_2__ r; } ;
struct iscsi_transport {struct iscsi_cls_session* (* create_session ) (struct iscsi_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct iscsi_internal {struct iscsi_transport* iscsi_transport; } ;
struct iscsi_endpoint {int dummy; } ;
struct iscsi_cls_session {int /*<<< orphan*/  sid; int /*<<< orphan*/  creator; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ISCSI_DBG_TRANS_SESSION (struct iscsi_cls_session*,char*) ; 
 struct Scsi_Host* iscsi_session_to_shost (struct iscsi_cls_session*) ; 
 struct iscsi_cls_session* stub1 (struct iscsi_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsi_if_create_session(struct iscsi_internal *priv, struct iscsi_endpoint *ep,
			struct iscsi_uevent *ev, pid_t pid,
			uint32_t initial_cmdsn,	uint16_t cmds_max,
			uint16_t queue_depth)
{
	struct iscsi_transport *transport = priv->iscsi_transport;
	struct iscsi_cls_session *session;
	struct Scsi_Host *shost;

	session = transport->create_session(ep, cmds_max, queue_depth,
					    initial_cmdsn);
	if (!session)
		return -ENOMEM;

	session->creator = pid;
	shost = iscsi_session_to_shost(session);
	ev->r.c_session_ret.host_no = shost->host_no;
	ev->r.c_session_ret.sid = session->sid;
	ISCSI_DBG_TRANS_SESSION(session,
				"Completed creating transport session\n");
	return 0;
}