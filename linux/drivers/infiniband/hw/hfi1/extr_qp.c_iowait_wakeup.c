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
struct rvt_qp {int dummy; } ;
struct iowait {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RVT_S_WAIT_DMA_DESC ; 
 int SDMA_AVAIL_REASON ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hfi1_qp_wakeup (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 struct rvt_qp* iowait_to_qp (struct iowait*) ; 

__attribute__((used)) static void iowait_wakeup(struct iowait *wait, int reason)
{
	struct rvt_qp *qp = iowait_to_qp(wait);

	WARN_ON(reason != SDMA_AVAIL_REASON);
	hfi1_qp_wakeup(qp, RVT_S_WAIT_DMA_DESC);
}