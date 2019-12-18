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
struct ib_wc {scalar_t__ status; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  nvme_rdma_wr_error (struct ib_cq*,struct ib_wc*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nvme_rdma_memreg_done(struct ib_cq *cq, struct ib_wc *wc)
{
	if (unlikely(wc->status != IB_WC_SUCCESS))
		nvme_rdma_wr_error(cq, wc, "MEMREG");
}