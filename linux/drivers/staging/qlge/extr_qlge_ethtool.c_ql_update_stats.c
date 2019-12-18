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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tx_pkts; } ;
struct ql_adapter {int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  xg_sem_mask; int /*<<< orphan*/  ndev; TYPE_1__ nic_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLGE_RCV_MAC_ERR_STATS ; 
 int /*<<< orphan*/  QL_DUMP_STAT (struct ql_adapter*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ql_read_xgmac_reg64 (struct ql_adapter*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ql_sem_spinlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_update_stats(struct ql_adapter *qdev)
{
	u32 i;
	u64 data;
	u64 *iter = &qdev->nic_stats.tx_pkts;

	spin_lock(&qdev->stats_lock);
	if (ql_sem_spinlock(qdev, qdev->xg_sem_mask)) {
		netif_err(qdev, drv, qdev->ndev,
			  "Couldn't get xgmac sem.\n");
		goto quit;
	}
	/*
	 * Get TX statistics.
	 */
	for (i = 0x200; i < 0x280; i += 8) {
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else
			*iter = data;
		iter++;
	}

	/*
	 * Get RX statistics.
	 */
	for (i = 0x300; i < 0x3d0; i += 8) {
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else
			*iter = data;
		iter++;
	}

	/* Update receive mac error statistics */
	iter += QLGE_RCV_MAC_ERR_STATS;

	/*
	 * Get Per-priority TX pause frame counter statistics.
	 */
	for (i = 0x500; i < 0x540; i += 8) {
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else
			*iter = data;
		iter++;
	}

	/*
	 * Get Per-priority RX pause frame counter statistics.
	 */
	for (i = 0x568; i < 0x5a8; i += 8) {
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else
			*iter = data;
		iter++;
	}

	/*
	 * Get RX NIC FIFO DROP statistics.
	 */
	if (ql_read_xgmac_reg64(qdev, 0x5b8, &data)) {
		netif_err(qdev, drv, qdev->ndev,
			  "Error reading status register 0x%.04x.\n", i);
		goto end;
	} else
		*iter = data;
end:
	ql_sem_unlock(qdev, qdev->xg_sem_mask);
quit:
	spin_unlock(&qdev->stats_lock);

	QL_DUMP_STAT(qdev);
}