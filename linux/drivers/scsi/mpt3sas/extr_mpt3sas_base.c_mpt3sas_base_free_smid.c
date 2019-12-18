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
typedef  scalar_t__ u16 ;
struct scsiio_tracker {int dummy; } ;
struct MPT3SAS_ADAPTER {scalar_t__ hi_priority_smid; scalar_t__ internal_smid; scalar_t__ hba_queue_depth; int /*<<< orphan*/  scsi_lookup_lock; int /*<<< orphan*/  internal_free_list; TYPE_2__* internal_lookup; int /*<<< orphan*/  hpr_free_list; TYPE_1__* hpr_lookup; int /*<<< orphan*/  request_sz; } ;
struct TYPE_4__ {int cb_idx; int /*<<< orphan*/  tracker_list; } ;
struct TYPE_3__ {int cb_idx; int /*<<< orphan*/  tracker_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  _base_recovery_check (struct MPT3SAS_ADAPTER*) ; 
 struct scsiio_tracker* _get_st_from_smid (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt3sas_base_clear_st (struct MPT3SAS_ADAPTER*,struct scsiio_tracker*) ; 
 void* mpt3sas_base_get_msg_frame (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
mpt3sas_base_free_smid(struct MPT3SAS_ADAPTER *ioc, u16 smid)
{
	unsigned long flags;
	int i;

	if (smid < ioc->hi_priority_smid) {
		struct scsiio_tracker *st;
		void *request;

		st = _get_st_from_smid(ioc, smid);
		if (!st) {
			_base_recovery_check(ioc);
			return;
		}

		/* Clear MPI request frame */
		request = mpt3sas_base_get_msg_frame(ioc, smid);
		memset(request, 0, ioc->request_sz);

		mpt3sas_base_clear_st(ioc, st);
		_base_recovery_check(ioc);
		return;
	}

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	if (smid < ioc->internal_smid) {
		/* hi-priority */
		i = smid - ioc->hi_priority_smid;
		ioc->hpr_lookup[i].cb_idx = 0xFF;
		list_add(&ioc->hpr_lookup[i].tracker_list, &ioc->hpr_free_list);
	} else if (smid <= ioc->hba_queue_depth) {
		/* internal queue */
		i = smid - ioc->internal_smid;
		ioc->internal_lookup[i].cb_idx = 0xFF;
		list_add(&ioc->internal_lookup[i].tracker_list,
		    &ioc->internal_free_list);
	}
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
}