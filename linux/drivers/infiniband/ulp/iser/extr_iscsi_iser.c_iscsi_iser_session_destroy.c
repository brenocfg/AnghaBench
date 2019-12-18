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
struct iscsi_cls_session {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_host_free (struct Scsi_Host*) ; 
 int /*<<< orphan*/  iscsi_host_remove (struct Scsi_Host*) ; 
 int /*<<< orphan*/  iscsi_session_teardown (struct iscsi_cls_session*) ; 
 struct Scsi_Host* iscsi_session_to_shost (struct iscsi_cls_session*) ; 

__attribute__((used)) static void
iscsi_iser_session_destroy(struct iscsi_cls_session *cls_session)
{
	struct Scsi_Host *shost = iscsi_session_to_shost(cls_session);

	iscsi_session_teardown(cls_session);
	iscsi_host_remove(shost);
	iscsi_host_free(shost);
}