#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct zfcp_erp_action {TYPE_3__* adapter; TYPE_4__* port; int /*<<< orphan*/  sdev; int /*<<< orphan*/  type; int /*<<< orphan*/  step; int /*<<< orphan*/  status; int /*<<< orphan*/  fsf_req_id; } ;
struct TYPE_6__ {void* rec_count; int /*<<< orphan*/  rec_action; int /*<<< orphan*/  rec_step; int /*<<< orphan*/  rec_status; int /*<<< orphan*/  fsf_req_id; } ;
struct TYPE_7__ {TYPE_1__ run; } ;
struct zfcp_dbf_rec {TYPE_2__ u; int /*<<< orphan*/  tag; int /*<<< orphan*/  id; } ;
struct zfcp_dbf {int /*<<< orphan*/  rec_lock; int /*<<< orphan*/  rec; struct zfcp_dbf_rec rec_buf; } ;
struct TYPE_10__ {int /*<<< orphan*/  erp_counter; } ;
struct TYPE_9__ {int /*<<< orphan*/  erp_counter; } ;
struct TYPE_8__ {int /*<<< orphan*/  erp_counter; struct zfcp_dbf* dbf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_REC_RUN ; 
 int /*<<< orphan*/  ZFCP_DBF_TAG_LEN ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int,struct zfcp_dbf_rec*,int) ; 
 int /*<<< orphan*/  debug_level_enabled (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_rec*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* sdev_to_zfcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_dbf_set_common (struct zfcp_dbf_rec*,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

void zfcp_dbf_rec_run_lvl(int level, char *tag, struct zfcp_erp_action *erp)
{
	struct zfcp_dbf *dbf = erp->adapter->dbf;
	struct zfcp_dbf_rec *rec = &dbf->rec_buf;
	unsigned long flags;

	if (!debug_level_enabled(dbf->rec, level))
		return;

	spin_lock_irqsave(&dbf->rec_lock, flags);
	memset(rec, 0, sizeof(*rec));

	rec->id = ZFCP_DBF_REC_RUN;
	memcpy(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	zfcp_dbf_set_common(rec, erp->adapter, erp->port, erp->sdev);

	rec->u.run.fsf_req_id = erp->fsf_req_id;
	rec->u.run.rec_status = erp->status;
	rec->u.run.rec_step = erp->step;
	rec->u.run.rec_action = erp->type;

	if (erp->sdev)
		rec->u.run.rec_count =
			atomic_read(&sdev_to_zfcp(erp->sdev)->erp_counter);
	else if (erp->port)
		rec->u.run.rec_count = atomic_read(&erp->port->erp_counter);
	else
		rec->u.run.rec_count = atomic_read(&erp->adapter->erp_counter);

	debug_event(dbf->rec, level, rec, sizeof(*rec));
	spin_unlock_irqrestore(&dbf->rec_lock, flags);
}