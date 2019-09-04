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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int PIDX_T5_V (scalar_t__) ; 
 int PIDX_V (scalar_t__) ; 
 int QID_V (scalar_t__) ; 
 int /*<<< orphan*/  SGE_PF_KDOORBELL_A ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int read_eq_indices (struct adapter*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

int cxgb4_sync_txq_pidx(struct net_device *dev, u16 qid, u16 pidx,
			u16 size)
{
	struct adapter *adap = netdev2adap(dev);
	u16 hw_pidx, hw_cidx;
	int ret;

	ret = read_eq_indices(adap, qid, &hw_pidx, &hw_cidx);
	if (ret)
		goto out;

	if (pidx != hw_pidx) {
		u16 delta;
		u32 val;

		if (pidx >= hw_pidx)
			delta = pidx - hw_pidx;
		else
			delta = size - hw_pidx + pidx;

		if (is_t4(adap->params.chip))
			val = PIDX_V(delta);
		else
			val = PIDX_T5_V(delta);
		wmb();
		t4_write_reg(adap, MYPF_REG(SGE_PF_KDOORBELL_A),
			     QID_V(qid) | val);
	}
out:
	return ret;
}