#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sge_qset {TYPE_2__* txq; scalar_t__ adap; } ;
struct TYPE_3__ {struct sge_qset* qs; } ;
struct adapter {TYPE_1__ sge; } ;
struct TYPE_4__ {int /*<<< orphan*/  cntxt_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_KDOORBELL ; 
 int F_SELEGRCNTX ; 
 int SGE_QSETS ; 
 int SGE_TXQ_PER_SET ; 
 int V_EGRCNTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ring_dbs(struct adapter *adap)
{
	int i, j;

	for (i = 0; i < SGE_QSETS; i++) {
		struct sge_qset *qs = &adap->sge.qs[i];

		if (qs->adap)
			for (j = 0; j < SGE_TXQ_PER_SET; j++)
				t3_write_reg(adap, A_SG_KDOORBELL, F_SELEGRCNTX | V_EGRCNTX(qs->txq[j].cntxt_id));
	}
}