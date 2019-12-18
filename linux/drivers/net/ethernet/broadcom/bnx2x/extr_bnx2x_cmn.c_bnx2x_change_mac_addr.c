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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  CURR_CFG_MET_OS ; 
 int EINVAL ; 
 scalar_t__ IS_MF_STORAGE_ONLY (struct bnx2x*) ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnx2x_set_eth_mac (struct bnx2x*,int) ; 
 int /*<<< orphan*/  curr_cfg ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

int bnx2x_change_mac_addr(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;
	struct bnx2x *bp = netdev_priv(dev);
	int rc = 0;

	if (!is_valid_ether_addr(addr->sa_data)) {
		BNX2X_ERR("Requested MAC address is not valid\n");
		return -EINVAL;
	}

	if (IS_MF_STORAGE_ONLY(bp)) {
		BNX2X_ERR("Can't change address on STORAGE ONLY function\n");
		return -EINVAL;
	}

	if (netif_running(dev))  {
		rc = bnx2x_set_eth_mac(bp, false);
		if (rc)
			return rc;
	}

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	if (netif_running(dev))
		rc = bnx2x_set_eth_mac(bp, true);

	if (IS_PF(bp) && SHMEM2_HAS(bp, curr_cfg))
		SHMEM2_WR(bp, curr_cfg, CURR_CFG_MET_OS);

	return rc;
}