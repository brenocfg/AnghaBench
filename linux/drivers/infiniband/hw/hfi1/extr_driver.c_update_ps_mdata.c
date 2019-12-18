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
struct ps_mdata {scalar_t__ ps_head; scalar_t__ rsize; scalar_t__ maxcnt; int ps_seq; } ;
struct hfi1_ctxtdata {scalar_t__ ctxt; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RTAIL ; 
 int /*<<< orphan*/  HFI1_CAP_KGET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HFI1_CTRL_CTXT ; 

__attribute__((used)) static inline void update_ps_mdata(struct ps_mdata *mdata,
				   struct hfi1_ctxtdata *rcd)
{
	mdata->ps_head += mdata->rsize;
	if (mdata->ps_head >= mdata->maxcnt)
		mdata->ps_head = 0;

	/* Control context must do seq counting */
	if (!HFI1_CAP_KGET_MASK(rcd->flags, DMA_RTAIL) ||
	    (rcd->ctxt == HFI1_CTRL_CTXT)) {
		if (++mdata->ps_seq > 13)
			mdata->ps_seq = 1;
	}
}