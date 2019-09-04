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
typedef  scalar_t__ u32 ;
struct sge_rspq {scalar_t__ pktcnt_idx; int intr_params; int /*<<< orphan*/  cntxt_id; scalar_t__ desc; } ;
struct adapter {int /*<<< orphan*/  sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PARAMS_MNEM_DMAQ ; 
 scalar_t__ FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DMAQ_IQ_INTCNTTHRESH ; 
 scalar_t__ FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_PARAMS_PARAM_YZ_V (int /*<<< orphan*/ ) ; 
 int QINTR_CNT_EN_V (int) ; 
 int QINTR_TIMER_IDX_V (unsigned int) ; 
 unsigned int SGE_TIMER_RSTRT_CNTR ; 
 scalar_t__ closest_thres (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int closest_timer (int /*<<< orphan*/ *,unsigned int) ; 
 int t4vf_set_params (struct adapter*,int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int set_rxq_intr_params(struct adapter *adapter, struct sge_rspq *rspq,
			       unsigned int us, unsigned int cnt)
{
	unsigned int timer_idx;

	/*
	 * If both the interrupt holdoff timer and count are specified as
	 * zero, default to a holdoff count of 1 ...
	 */
	if ((us | cnt) == 0)
		cnt = 1;

	/*
	 * If an interrupt holdoff count has been specified, then find the
	 * closest configured holdoff count and use that.  If the response
	 * queue has already been created, then update its queue context
	 * parameters ...
	 */
	if (cnt) {
		int err;
		u32 v, pktcnt_idx;

		pktcnt_idx = closest_thres(&adapter->sge, cnt);
		if (rspq->desc && rspq->pktcnt_idx != pktcnt_idx) {
			v = FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
			    FW_PARAMS_PARAM_X_V(
					FW_PARAMS_PARAM_DMAQ_IQ_INTCNTTHRESH) |
			    FW_PARAMS_PARAM_YZ_V(rspq->cntxt_id);
			err = t4vf_set_params(adapter, 1, &v, &pktcnt_idx);
			if (err)
				return err;
		}
		rspq->pktcnt_idx = pktcnt_idx;
	}

	/*
	 * Compute the closest holdoff timer index from the supplied holdoff
	 * timer value.
	 */
	timer_idx = (us == 0
		     ? SGE_TIMER_RSTRT_CNTR
		     : closest_timer(&adapter->sge, us));

	/*
	 * Update the response queue's interrupt coalescing parameters and
	 * return success.
	 */
	rspq->intr_params = (QINTR_TIMER_IDX_V(timer_idx) |
			     QINTR_CNT_EN_V(cnt > 0));
	return 0;
}