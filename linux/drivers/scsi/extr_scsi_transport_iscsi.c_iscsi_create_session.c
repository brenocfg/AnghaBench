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
struct iscsi_transport {int dummy; } ;
struct iscsi_cls_session {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 scalar_t__ iscsi_add_session (struct iscsi_cls_session*,unsigned int) ; 
 struct iscsi_cls_session* iscsi_alloc_session (struct Scsi_Host*,struct iscsi_transport*,int) ; 
 int /*<<< orphan*/  iscsi_free_session (struct iscsi_cls_session*) ; 

struct iscsi_cls_session *
iscsi_create_session(struct Scsi_Host *shost, struct iscsi_transport *transport,
		     int dd_size, unsigned int target_id)
{
	struct iscsi_cls_session *session;

	session = iscsi_alloc_session(shost, transport, dd_size);
	if (!session)
		return NULL;

	if (iscsi_add_session(session, target_id)) {
		iscsi_free_session(session);
		return NULL;
	}
	return session;
}