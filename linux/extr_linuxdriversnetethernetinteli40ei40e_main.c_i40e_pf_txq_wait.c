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
typedef  int u32 ;
struct i40e_pf {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I40E_QTX_ENA (int) ; 
 int I40E_QTX_ENA_QENA_STAT_MASK ; 
 int I40E_QUEUE_WAIT_RETRY_LIMIT ; 
 int rd32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int i40e_pf_txq_wait(struct i40e_pf *pf, int pf_q, bool enable)
{
	int i;
	u32 tx_reg;

	for (i = 0; i < I40E_QUEUE_WAIT_RETRY_LIMIT; i++) {
		tx_reg = rd32(&pf->hw, I40E_QTX_ENA(pf_q));
		if (enable == !!(tx_reg & I40E_QTX_ENA_QENA_STAT_MASK))
			break;

		usleep_range(10, 20);
	}
	if (i >= I40E_QUEUE_WAIT_RETRY_LIMIT)
		return -ETIMEDOUT;

	return 0;
}