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
typedef  scalar_t__ u16 ;
struct bfi_msg_s {int dummy; } ;
struct bfi_ioim_rsp_s {int io_status; int reuse_io_tag; int abort_tag; int /*<<< orphan*/  io_tag; } ;
struct bfa_s {int dummy; } ;
struct bfa_ioim_s {scalar_t__ iotag; int abort_tag; int /*<<< orphan*/  itnim; int /*<<< orphan*/  bfa; TYPE_1__* iosp; } ;
struct bfa_fcpim_s {int dummy; } ;
typedef  enum bfa_ioim_event { ____Placeholder_bfa_ioim_event } bfa_ioim_event ;
struct TYPE_2__ {struct bfi_msg_s comp_rspmsg; } ;

/* Variables and functions */
 struct bfa_fcpim_s* BFA_FCPIM (struct bfa_s*) ; 
 struct bfa_ioim_s* BFA_IOIM_FROM_TAG (struct bfa_fcpim_s*,scalar_t__) ; 
 int BFA_IOIM_SM_ABORT_COMP ; 
 int BFA_IOIM_SM_ABORT_DONE ; 
 int BFA_IOIM_SM_COMP ; 
 int BFA_IOIM_SM_COMP_UTAG ; 
 int BFA_IOIM_SM_DONE ; 
 int BFA_IOIM_SM_FREE ; 
 int BFA_IOIM_SM_SQRETRY ; 
#define  BFI_IOIM_STS_ABORTED 135 
#define  BFI_IOIM_STS_HOST_ABORTED 134 
#define  BFI_IOIM_STS_OK 133 
#define  BFI_IOIM_STS_PROTO_ERR 132 
#define  BFI_IOIM_STS_RES_FREE 131 
#define  BFI_IOIM_STS_SQER_NEEDED 130 
#define  BFI_IOIM_STS_TIMEDOUT 129 
#define  BFI_IOIM_STS_UTAG 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioim_sm_active ; 
 scalar_t__ bfa_sm_cmp_state (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_ioim_s*,int) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iocom_hostabrts ; 
 int /*<<< orphan*/  iocom_proto_err ; 
 int /*<<< orphan*/  iocom_res_free ; 
 int /*<<< orphan*/  iocom_sqer_needed ; 
 int /*<<< orphan*/  iocom_utags ; 
 int /*<<< orphan*/  iocomp_aborted ; 
 int /*<<< orphan*/  iocomp_ok ; 
 int /*<<< orphan*/  iocomp_timedout ; 

void
bfa_ioim_isr(struct bfa_s *bfa, struct bfi_msg_s *m)
{
	struct bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	struct bfi_ioim_rsp_s *rsp = (struct bfi_ioim_rsp_s *) m;
	struct bfa_ioim_s *ioim;
	u16	iotag;
	enum bfa_ioim_event evt = BFA_IOIM_SM_COMP;

	iotag = be16_to_cpu(rsp->io_tag);

	ioim = BFA_IOIM_FROM_TAG(fcpim, iotag);
	WARN_ON(ioim->iotag != iotag);

	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, rsp->io_status);
	bfa_trc(ioim->bfa, rsp->reuse_io_tag);

	if (bfa_sm_cmp_state(ioim, bfa_ioim_sm_active))
		ioim->iosp->comp_rspmsg = *m;

	switch (rsp->io_status) {
	case BFI_IOIM_STS_OK:
		bfa_stats(ioim->itnim, iocomp_ok);
		if (rsp->reuse_io_tag == 0)
			evt = BFA_IOIM_SM_DONE;
		else
			evt = BFA_IOIM_SM_COMP;
		break;

	case BFI_IOIM_STS_TIMEDOUT:
		bfa_stats(ioim->itnim, iocomp_timedout);
		/* fall through */
	case BFI_IOIM_STS_ABORTED:
		rsp->io_status = BFI_IOIM_STS_ABORTED;
		bfa_stats(ioim->itnim, iocomp_aborted);
		if (rsp->reuse_io_tag == 0)
			evt = BFA_IOIM_SM_DONE;
		else
			evt = BFA_IOIM_SM_COMP;
		break;

	case BFI_IOIM_STS_PROTO_ERR:
		bfa_stats(ioim->itnim, iocom_proto_err);
		WARN_ON(!rsp->reuse_io_tag);
		evt = BFA_IOIM_SM_COMP;
		break;

	case BFI_IOIM_STS_SQER_NEEDED:
		bfa_stats(ioim->itnim, iocom_sqer_needed);
		WARN_ON(rsp->reuse_io_tag != 0);
		evt = BFA_IOIM_SM_SQRETRY;
		break;

	case BFI_IOIM_STS_RES_FREE:
		bfa_stats(ioim->itnim, iocom_res_free);
		evt = BFA_IOIM_SM_FREE;
		break;

	case BFI_IOIM_STS_HOST_ABORTED:
		bfa_stats(ioim->itnim, iocom_hostabrts);
		if (rsp->abort_tag != ioim->abort_tag) {
			bfa_trc(ioim->bfa, rsp->abort_tag);
			bfa_trc(ioim->bfa, ioim->abort_tag);
			return;
		}

		if (rsp->reuse_io_tag)
			evt = BFA_IOIM_SM_ABORT_COMP;
		else
			evt = BFA_IOIM_SM_ABORT_DONE;
		break;

	case BFI_IOIM_STS_UTAG:
		bfa_stats(ioim->itnim, iocom_utags);
		evt = BFA_IOIM_SM_COMP_UTAG;
		break;

	default:
		WARN_ON(1);
	}

	bfa_sm_send_event(ioim, evt);
}