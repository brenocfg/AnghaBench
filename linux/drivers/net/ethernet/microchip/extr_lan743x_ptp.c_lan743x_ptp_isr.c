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
struct lan743x_ptp {int /*<<< orphan*/  ptp_clock; } ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; struct lan743x_ptp ptp; } ;

/* Variables and functions */
 int INT_BIT_1588_ ; 
 int /*<<< orphan*/  INT_EN_CLR ; 
 int /*<<< orphan*/  INT_EN_SET ; 
 int PTP_INT_BIT_TIMER_A_ ; 
 int PTP_INT_BIT_TIMER_B_ ; 
 int PTP_INT_BIT_TX_SWTS_ERR_ ; 
 int PTP_INT_BIT_TX_TS_ ; 
 int /*<<< orphan*/  PTP_INT_EN_SET ; 
 int /*<<< orphan*/  PTP_INT_STS ; 
 int /*<<< orphan*/  drv ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_err (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ptp_schedule_worker (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lan743x_ptp_isr(void *context)
{
	struct lan743x_adapter *adapter = (struct lan743x_adapter *)context;
	struct lan743x_ptp *ptp = NULL;
	int enable_flag = 1;
	u32 ptp_int_sts = 0;

	ptp = &adapter->ptp;

	lan743x_csr_write(adapter, INT_EN_CLR, INT_BIT_1588_);

	ptp_int_sts = lan743x_csr_read(adapter, PTP_INT_STS);
	ptp_int_sts &= lan743x_csr_read(adapter, PTP_INT_EN_SET);

	if (ptp_int_sts & PTP_INT_BIT_TX_TS_) {
		ptp_schedule_worker(ptp->ptp_clock, 0);
		enable_flag = 0;/* tasklet will re-enable later */
	}
	if (ptp_int_sts & PTP_INT_BIT_TX_SWTS_ERR_) {
		netif_err(adapter, drv, adapter->netdev,
			  "PTP TX Software Timestamp Error\n");
		/* clear int status bit */
		lan743x_csr_write(adapter, PTP_INT_STS,
				  PTP_INT_BIT_TX_SWTS_ERR_);
	}
	if (ptp_int_sts & PTP_INT_BIT_TIMER_B_) {
		/* clear int status bit */
		lan743x_csr_write(adapter, PTP_INT_STS,
				  PTP_INT_BIT_TIMER_B_);
	}
	if (ptp_int_sts & PTP_INT_BIT_TIMER_A_) {
		/* clear int status bit */
		lan743x_csr_write(adapter, PTP_INT_STS,
				  PTP_INT_BIT_TIMER_A_);
	}

	if (enable_flag) {
		/* re-enable isr */
		lan743x_csr_write(adapter, INT_EN_SET, INT_BIT_1588_);
	}
}