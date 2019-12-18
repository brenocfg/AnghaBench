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
struct xgbe_prv_data {int* pfcq; int /*<<< orphan*/  rx_q_count; TYPE_1__* pfc; } ;
struct TYPE_2__ {int /*<<< orphan*/  pfc_en; } ;

/* Variables and functions */
 unsigned int XGMAC_PRIO_QUEUES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_is_pfc_queue (struct xgbe_prv_data*,unsigned int) ; 

__attribute__((used)) static unsigned int xgbe_get_pfc_queues(struct xgbe_prv_data *pdata)
{
	unsigned int count, prio_queues;
	unsigned int i;

	if (!pdata->pfc->pfc_en)
		return 0;

	count = 0;
	prio_queues = XGMAC_PRIO_QUEUES(pdata->rx_q_count);
	for (i = 0; i < prio_queues; i++) {
		if (!xgbe_is_pfc_queue(pdata, i))
			continue;

		pdata->pfcq[i] = 1;
		count++;
	}

	return count;
}