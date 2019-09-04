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
struct xgbe_prv_data {unsigned int rx_q_count; } ;

/* Variables and functions */
 unsigned int XGMAC_FIFO_UNIT ; 
 int /*<<< orphan*/  xgbe_queue_flow_control_threshold (struct xgbe_prv_data*,unsigned int,unsigned int) ; 

__attribute__((used)) static void xgbe_calculate_flow_control_threshold(struct xgbe_prv_data *pdata,
						  unsigned int *fifo)
{
	unsigned int q_fifo_size;
	unsigned int i;

	for (i = 0; i < pdata->rx_q_count; i++) {
		q_fifo_size = (fifo[i] + 1) * XGMAC_FIFO_UNIT;

		xgbe_queue_flow_control_threshold(pdata, i, q_fifo_size);
	}
}