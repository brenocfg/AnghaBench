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
typedef  int /*<<< orphan*/  u64 ;
struct ps_mdata {scalar_t__ ps_head; scalar_t__ ps_tail; scalar_t__ ps_seq; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RTAIL ; 
 scalar_t__ HFI1_CAP_KGET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rhf_rcv_seq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ps_done(struct ps_mdata *mdata, u64 rhf,
			  struct hfi1_ctxtdata *rcd)
{
	if (HFI1_CAP_KGET_MASK(rcd->flags, DMA_RTAIL))
		return mdata->ps_head == mdata->ps_tail;
	return mdata->ps_seq != rhf_rcv_seq(rhf);
}