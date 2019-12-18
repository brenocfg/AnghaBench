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
typedef  unsigned int u32 ;
struct xgene_enet_pdata {struct net_device* ndev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_BLOCK_MEM_RDY_ADDR ; 
 int /*<<< orphan*/  ENET_CFG_MEM_RAM_SHUTDOWN_ADDR ; 
 int ENODEV ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 unsigned int xgene_enet_rd_diag_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_wr_diag_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_enet_ecc_init(struct xgene_enet_pdata *p)
{
	struct net_device *ndev = p->ndev;
	u32 data, shutdown;
	int i = 0;

	shutdown = xgene_enet_rd_diag_csr(p, ENET_CFG_MEM_RAM_SHUTDOWN_ADDR);
	data = xgene_enet_rd_diag_csr(p, ENET_BLOCK_MEM_RDY_ADDR);

	if (!shutdown && data == ~0U) {
		netdev_dbg(ndev, "+ ecc_init done, skipping\n");
		return 0;
	}

	xgene_enet_wr_diag_csr(p, ENET_CFG_MEM_RAM_SHUTDOWN_ADDR, 0);
	do {
		usleep_range(100, 110);
		data = xgene_enet_rd_diag_csr(p, ENET_BLOCK_MEM_RDY_ADDR);
		if (data == ~0U)
			return 0;
	} while (++i < 10);

	netdev_err(ndev, "Failed to release memory from shutdown\n");
	return -ENODEV;
}