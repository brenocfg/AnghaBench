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
struct ib_wc {scalar_t__ status; TYPE_1__* wr_cqe; } ;
struct ib_cq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* done ) (struct ib_cq*,struct ib_wc*) ;} ;

/* Variables and functions */
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int ib_poll_cq (struct ib_cq*,int /*<<< orphan*/ ,struct ib_wc*) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct ib_cq*,struct ib_wc*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int __ib_process_cq(struct ib_cq *cq, int budget, struct ib_wc *wcs,
			   int batch)
{
	int i, n, completed = 0;

	/*
	 * budget might be (-1) if the caller does not
	 * want to bound this call, thus we need unsigned
	 * minimum here.
	 */
	while ((n = ib_poll_cq(cq, min_t(u32, batch,
					 budget - completed), wcs)) > 0) {
		for (i = 0; i < n; i++) {
			struct ib_wc *wc = &wcs[i];

			if (wc->wr_cqe)
				wc->wr_cqe->done(cq, wc);
			else
				WARN_ON_ONCE(wc->status == IB_WC_SUCCESS);
		}

		completed += n;

		if (n != batch || (budget != -1 && completed >= budget))
			break;
	}

	return completed;
}