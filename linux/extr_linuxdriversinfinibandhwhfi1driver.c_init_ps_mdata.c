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
struct ps_mdata {int /*<<< orphan*/  ps_seq; int /*<<< orphan*/  ps_tail; int /*<<< orphan*/  ps_head; int /*<<< orphan*/  maxcnt; int /*<<< orphan*/  rsize; struct hfi1_ctxtdata* rcd; } ;
struct hfi1_packet {int /*<<< orphan*/  rhqoff; int /*<<< orphan*/  maxcnt; int /*<<< orphan*/  rsize; struct hfi1_ctxtdata* rcd; } ;
struct hfi1_ctxtdata {scalar_t__ ctxt; int /*<<< orphan*/  seq_cnt; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RTAIL ; 
 scalar_t__ HFI1_CAP_KGET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HFI1_CTRL_CTXT ; 
 int /*<<< orphan*/  get_rcvhdrtail (struct hfi1_ctxtdata*) ; 

__attribute__((used)) static inline void init_ps_mdata(struct ps_mdata *mdata,
				 struct hfi1_packet *packet)
{
	struct hfi1_ctxtdata *rcd = packet->rcd;

	mdata->rcd = rcd;
	mdata->rsize = packet->rsize;
	mdata->maxcnt = packet->maxcnt;
	mdata->ps_head = packet->rhqoff;

	if (HFI1_CAP_KGET_MASK(rcd->flags, DMA_RTAIL)) {
		mdata->ps_tail = get_rcvhdrtail(rcd);
		if (rcd->ctxt == HFI1_CTRL_CTXT)
			mdata->ps_seq = rcd->seq_cnt;
		else
			mdata->ps_seq = 0; /* not used with DMA_RTAIL */
	} else {
		mdata->ps_tail = 0; /* used only with DMA_RTAIL*/
		mdata->ps_seq = rcd->seq_cnt;
	}
}