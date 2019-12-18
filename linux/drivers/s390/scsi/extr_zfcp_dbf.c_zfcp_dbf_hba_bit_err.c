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
struct zfcp_fsf_req {int /*<<< orphan*/  status; int /*<<< orphan*/  req_id; struct fsf_status_read_buffer* data; TYPE_1__* adapter; } ;
struct TYPE_5__ {int /*<<< orphan*/  be; } ;
struct zfcp_dbf_hba {TYPE_2__ u; int /*<<< orphan*/  fsf_cmd; int /*<<< orphan*/  fsf_req_status; int /*<<< orphan*/  fsf_req_id; int /*<<< orphan*/  id; int /*<<< orphan*/ * tag; } ;
struct zfcp_dbf {int /*<<< orphan*/  hba_lock; int /*<<< orphan*/  hba; struct zfcp_dbf_hba hba_buf; } ;
struct TYPE_6__ {char bit_error; } ;
struct fsf_status_read_buffer {TYPE_3__ payload; } ;
struct fsf_bit_error_payload {int dummy; } ;
struct TYPE_4__ {struct zfcp_dbf* dbf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSF_QTCB_UNSOLICITED_STATUS ; 
 int /*<<< orphan*/  ZFCP_DBF_HBA_BIT ; 
 int ZFCP_DBF_TAG_LEN ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int const,struct zfcp_dbf_hba*,int) ; 
 int /*<<< orphan*/  debug_level_enabled (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void zfcp_dbf_hba_bit_err(char *tag, struct zfcp_fsf_req *req)
{
	struct zfcp_dbf *dbf = req->adapter->dbf;
	struct zfcp_dbf_hba *rec = &dbf->hba_buf;
	struct fsf_status_read_buffer *sr_buf = req->data;
	static int const level = 1;
	unsigned long flags;

	if (unlikely(!debug_level_enabled(dbf->hba, level)))
		return;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	memset(rec, 0, sizeof(*rec));

	memcpy(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->id = ZFCP_DBF_HBA_BIT;
	rec->fsf_req_id = req->req_id;
	rec->fsf_req_status = req->status;
	rec->fsf_cmd = FSF_QTCB_UNSOLICITED_STATUS;
	memcpy(&rec->u.be, &sr_buf->payload.bit_error,
	       sizeof(struct fsf_bit_error_payload));

	debug_event(dbf->hba, level, rec, sizeof(*rec));
	spin_unlock_irqrestore(&dbf->hba_lock, flags);
}