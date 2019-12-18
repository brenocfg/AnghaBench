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
struct pci_dev {int dummy; } ;
struct TYPE_4__ {struct ocrdma_dev* dev; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct ocrdma_dev {TYPE_2__ reset_stats; int /*<<< orphan*/  dir; TYPE_2__ driver_stats; TYPE_2__ rx_dbg_stats; TYPE_2__ tx_dbg_stats; TYPE_2__ rx_qp_err_stats; TYPE_2__ tx_qp_err_stats; TYPE_2__ db_err_stats; TYPE_2__ tx_stats; TYPE_2__ wqe_stats; TYPE_2__ rx_stats; TYPE_2__ rsrc_stats; TYPE_1__ nic_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_DB_ERRSTATS ; 
 int /*<<< orphan*/  OCRDMA_DRV_STATS ; 
 int /*<<< orphan*/  OCRDMA_RESET_STATS ; 
 int /*<<< orphan*/  OCRDMA_RSRC_STATS ; 
 int /*<<< orphan*/  OCRDMA_RXQP_ERRSTATS ; 
 int /*<<< orphan*/  OCRDMA_RXSTATS ; 
 int /*<<< orphan*/  OCRDMA_RX_DBG_STATS ; 
 int /*<<< orphan*/  OCRDMA_TXQP_ERRSTATS ; 
 int /*<<< orphan*/  OCRDMA_TXSTATS ; 
 int /*<<< orphan*/  OCRDMA_TX_DBG_STATS ; 
 int /*<<< orphan*/  OCRDMA_WQESTATS ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocrdma_dbg_ops ; 
 int /*<<< orphan*/  ocrdma_dbgfs_dir ; 
 int /*<<< orphan*/  pci_name (struct pci_dev const*) ; 

void ocrdma_add_port_stats(struct ocrdma_dev *dev)
{
	const struct pci_dev *pdev = dev->nic_info.pdev;

	if (!ocrdma_dbgfs_dir)
		return;

	/* Create post stats base dir */
	dev->dir = debugfs_create_dir(pci_name(pdev), ocrdma_dbgfs_dir);

	dev->rsrc_stats.type = OCRDMA_RSRC_STATS;
	dev->rsrc_stats.dev = dev;
	debugfs_create_file("resource_stats", S_IRUSR, dev->dir,
			    &dev->rsrc_stats, &ocrdma_dbg_ops);

	dev->rx_stats.type = OCRDMA_RXSTATS;
	dev->rx_stats.dev = dev;
	debugfs_create_file("rx_stats", S_IRUSR, dev->dir, &dev->rx_stats,
			    &ocrdma_dbg_ops);

	dev->wqe_stats.type = OCRDMA_WQESTATS;
	dev->wqe_stats.dev = dev;
	debugfs_create_file("wqe_stats", S_IRUSR, dev->dir, &dev->wqe_stats,
			    &ocrdma_dbg_ops);

	dev->tx_stats.type = OCRDMA_TXSTATS;
	dev->tx_stats.dev = dev;
	debugfs_create_file("tx_stats", S_IRUSR, dev->dir, &dev->tx_stats,
			    &ocrdma_dbg_ops);

	dev->db_err_stats.type = OCRDMA_DB_ERRSTATS;
	dev->db_err_stats.dev = dev;
	debugfs_create_file("db_err_stats", S_IRUSR, dev->dir,
			    &dev->db_err_stats, &ocrdma_dbg_ops);

	dev->tx_qp_err_stats.type = OCRDMA_TXQP_ERRSTATS;
	dev->tx_qp_err_stats.dev = dev;
	debugfs_create_file("tx_qp_err_stats", S_IRUSR, dev->dir,
			    &dev->tx_qp_err_stats, &ocrdma_dbg_ops);

	dev->rx_qp_err_stats.type = OCRDMA_RXQP_ERRSTATS;
	dev->rx_qp_err_stats.dev = dev;
	debugfs_create_file("rx_qp_err_stats", S_IRUSR, dev->dir,
			    &dev->rx_qp_err_stats, &ocrdma_dbg_ops);

	dev->tx_dbg_stats.type = OCRDMA_TX_DBG_STATS;
	dev->tx_dbg_stats.dev = dev;
	debugfs_create_file("tx_dbg_stats", S_IRUSR, dev->dir,
			    &dev->tx_dbg_stats, &ocrdma_dbg_ops);

	dev->rx_dbg_stats.type = OCRDMA_RX_DBG_STATS;
	dev->rx_dbg_stats.dev = dev;
	debugfs_create_file("rx_dbg_stats", S_IRUSR, dev->dir,
			    &dev->rx_dbg_stats, &ocrdma_dbg_ops);

	dev->driver_stats.type = OCRDMA_DRV_STATS;
	dev->driver_stats.dev = dev;
	debugfs_create_file("driver_dbg_stats", S_IRUSR, dev->dir,
			    &dev->driver_stats, &ocrdma_dbg_ops);

	dev->reset_stats.type = OCRDMA_RESET_STATS;
	dev->reset_stats.dev = dev;
	debugfs_create_file("reset_stats", 0200, dev->dir, &dev->reset_stats,
			    &ocrdma_dbg_ops);
}