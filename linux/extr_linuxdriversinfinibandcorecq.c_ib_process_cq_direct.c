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
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int IB_POLL_BATCH_DIRECT ; 
 int __ib_process_cq (struct ib_cq*,int,struct ib_wc*,int) ; 

int ib_process_cq_direct(struct ib_cq *cq, int budget)
{
	struct ib_wc wcs[IB_POLL_BATCH_DIRECT];

	return __ib_process_cq(cq, budget, wcs, IB_POLL_BATCH_DIRECT);
}