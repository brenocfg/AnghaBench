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
typedef  scalar_t__ u32 ;
struct xge_pdata {TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_MEM_RDY ; 
 int /*<<< orphan*/  CFG_MEM_RAM_SHUTDOWN ; 
 int DEVM_ARAUX_COH ; 
 int DEVM_AWAUX_COH ; 
 int /*<<< orphan*/  ENET_CLKEN ; 
 int /*<<< orphan*/  ENET_SHIM ; 
 int /*<<< orphan*/  ENET_SRST ; 
 int ETIMEDOUT ; 
 scalar_t__ MEM_RDY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 scalar_t__ xge_rd_csr (struct xge_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,int) ; 

int xge_port_reset(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct device *dev = &pdata->pdev->dev;
	u32 data, wait = 10;

	xge_wr_csr(pdata, ENET_CLKEN, 0x3);
	xge_wr_csr(pdata, ENET_SRST, 0xf);
	xge_wr_csr(pdata, ENET_SRST, 0);
	xge_wr_csr(pdata, CFG_MEM_RAM_SHUTDOWN, 1);
	xge_wr_csr(pdata, CFG_MEM_RAM_SHUTDOWN, 0);

	do {
		usleep_range(100, 110);
		data = xge_rd_csr(pdata, BLOCK_MEM_RDY);
	} while (data != MEM_RDY && wait--);

	if (data != MEM_RDY) {
		dev_err(dev, "ECC init failed: %x\n", data);
		return -ETIMEDOUT;
	}

	xge_wr_csr(pdata, ENET_SHIM, DEVM_ARAUX_COH | DEVM_AWAUX_COH);

	return 0;
}