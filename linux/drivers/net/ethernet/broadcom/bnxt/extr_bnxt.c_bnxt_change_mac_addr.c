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
struct bnxt {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int bnxt_approve_mac (struct bnxt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnxt_close_nic (struct bnxt*,int,int) ; 
 int bnxt_open_nic (struct bnxt*,int,int) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bnxt_change_mac_addr(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;
	struct bnxt *bp = netdev_priv(dev);
	int rc = 0;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (ether_addr_equal(addr->sa_data, dev->dev_addr))
		return 0;

	rc = bnxt_approve_mac(bp, addr->sa_data, true);
	if (rc)
		return rc;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	if (netif_running(dev)) {
		bnxt_close_nic(bp, false, false);
		rc = bnxt_open_nic(bp, false, false);
	}

	return rc;
}