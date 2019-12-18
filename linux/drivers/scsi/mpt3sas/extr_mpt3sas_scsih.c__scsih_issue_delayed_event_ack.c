#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct MPT3SAS_ADAPTER {int internal_smid; int /*<<< orphan*/  (* put_smid_default ) (struct MPT3SAS_ADAPTER*,int) ;int /*<<< orphan*/  base_cb_idx; int /*<<< orphan*/  scsi_lookup_lock; TYPE_1__* internal_lookup; } ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_6__ {scalar_t__ VP_ID; scalar_t__ VF_ID; int /*<<< orphan*/  EventContext; int /*<<< orphan*/  Event; int /*<<< orphan*/  Function; } ;
struct TYPE_5__ {int /*<<< orphan*/  cb_idx; } ;
typedef  TYPE_2__ Mpi2EventAckRequest_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_FUNCTION_EVENT_ACK ; 
 int /*<<< orphan*/  dewtprintk (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* mpt3sas_base_get_msg_frame (struct MPT3SAS_ADAPTER*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct MPT3SAS_ADAPTER*,int) ; 

__attribute__((used)) static void
_scsih_issue_delayed_event_ack(struct MPT3SAS_ADAPTER *ioc, u16 smid, U16 event,
				U32 event_context)
{
	Mpi2EventAckRequest_t *ack_request;
	int i = smid - ioc->internal_smid;
	unsigned long flags;

	/* Without releasing the smid just update the
	 * call back index and reuse the same smid for
	 * processing this delayed request
	 */
	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	ioc->internal_lookup[i].cb_idx = ioc->base_cb_idx;
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);

	dewtprintk(ioc,
		   ioc_info(ioc, "EVENT ACK: event(0x%04x), smid(%d), cb(%d)\n",
			    le16_to_cpu(event), smid, ioc->base_cb_idx));
	ack_request = mpt3sas_base_get_msg_frame(ioc, smid);
	memset(ack_request, 0, sizeof(Mpi2EventAckRequest_t));
	ack_request->Function = MPI2_FUNCTION_EVENT_ACK;
	ack_request->Event = event;
	ack_request->EventContext = event_context;
	ack_request->VF_ID = 0;  /* TODO */
	ack_request->VP_ID = 0;
	ioc->put_smid_default(ioc, smid);
}