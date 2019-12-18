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
struct hfi1_ctxtdata {scalar_t__ ctxt; } ;

/* Variables and functions */
 scalar_t__ HFI1_CTRL_CTXT ; 
 scalar_t__ rhf_rcv_seq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ps_skip(struct ps_mdata *mdata, u64 rhf,
			  struct hfi1_ctxtdata *rcd)
{
	/*
	 * Control context can potentially receive an invalid rhf.
	 * Drop such packets.
	 */
	if ((rcd->ctxt == HFI1_CTRL_CTXT) && (mdata->ps_head != mdata->ps_tail))
		return mdata->ps_seq != rhf_rcv_seq(rhf);

	return 0;
}