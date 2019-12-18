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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  cntxt_id; } ;
struct sge_eth_txq {int dbqtimerix; TYPE_1__ q; } ;
struct sge {int* dbqtimer_val; struct sge_eth_txq* ethtxq; } ;
struct port_info {size_t first_qset; int nqsets; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {int flags; int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; struct sge sge; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int CXGB4_FULL_INIT_DONE ; 
 int CXGB4_SGE_DBQ_TIMER ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DMAQ ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DMAQ_EQ_TIMERIX ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_YZ_V (int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4_set_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static int set_dbqtimer(struct net_device *dev, int usecs)
{
	int qix, timerix, min_timerix, delta, min_delta;
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adap = pi->adapter;
	struct sge *s = &adap->sge;
	struct sge_eth_txq *txq;
	u32 param, val;
	int ret;

	if (!(adap->flags & CXGB4_SGE_DBQ_TIMER))
		return 0;

	/* Find the SGE Doorbell Timer Value that's closest to the requested
	 * value.
	 */
	min_delta = INT_MAX;
	min_timerix = 0;
	for (timerix = 0; timerix < ARRAY_SIZE(s->dbqtimer_val); timerix++) {
		delta = s->dbqtimer_val[timerix] - usecs;
		if (delta < 0)
			delta = -delta;
		if (delta < min_delta) {
			min_delta = delta;
			min_timerix = timerix;
		}
	}

	/* Return early if it's the same Timer Index we're already using.
	 * We use the same Timer Index for all of the TX Queues for an
	 * interface so it's only necessary to check the first one.
	 */
	txq = &s->ethtxq[pi->first_qset];
	if (txq->dbqtimerix == min_timerix)
		return 0;

	for (qix = 0; qix < pi->nqsets; qix++, txq++) {
		if (adap->flags & CXGB4_FULL_INIT_DONE) {
			param =
			 (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
			  FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DMAQ_EQ_TIMERIX) |
			  FW_PARAMS_PARAM_YZ_V(txq->q.cntxt_id));
			val = min_timerix;
			ret = t4_set_params(adap, adap->mbox, adap->pf, 0,
					    1, &param, &val);
			if (ret)
				return ret;
		}
		txq->dbqtimerix = min_timerix;
	}
	return 0;
}