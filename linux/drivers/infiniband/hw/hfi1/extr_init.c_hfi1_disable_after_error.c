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
typedef  scalar_t__ u32 ;
struct hfi1_pportdata {int /*<<< orphan*/ * statusp; } ;
struct hfi1_devdata {int flags; scalar_t__ num_pports; TYPE_1__* status; struct hfi1_pportdata* pport; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HFI1_INITTED ; 
 int HFI1_PRESENT ; 
 int /*<<< orphan*/  HFI1_STATUS_HWERROR ; 
 int /*<<< orphan*/  HFI1_STATUS_IB_READY ; 
 int /*<<< orphan*/  HLS_DN_DISABLE ; 
 int /*<<< orphan*/  set_link_state (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 

void hfi1_disable_after_error(struct hfi1_devdata *dd)
{
	if (dd->flags & HFI1_INITTED) {
		u32 pidx;

		dd->flags &= ~HFI1_INITTED;
		if (dd->pport)
			for (pidx = 0; pidx < dd->num_pports; ++pidx) {
				struct hfi1_pportdata *ppd;

				ppd = dd->pport + pidx;
				if (dd->flags & HFI1_PRESENT)
					set_link_state(ppd, HLS_DN_DISABLE);

				if (ppd->statusp)
					*ppd->statusp &= ~HFI1_STATUS_IB_READY;
			}
	}

	/*
	 * Mark as having had an error for driver, and also
	 * for /sys and status word mapped to user programs.
	 * This marks unit as not usable, until reset.
	 */
	if (dd->status)
		dd->status->dev |= HFI1_STATUS_HWERROR;
}