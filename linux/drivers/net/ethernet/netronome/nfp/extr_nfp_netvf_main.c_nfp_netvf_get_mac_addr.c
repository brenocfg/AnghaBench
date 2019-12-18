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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {TYPE_2__* netdev; } ;
struct nfp_net {TYPE_1__ dp; } ;
struct TYPE_4__ {int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ NFP_NET_CFG_MACADDR ; 
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_2__*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_readl (struct nfp_net*,scalar_t__) ; 
 int /*<<< orphan*/  nn_readw (struct nfp_net*,scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_netvf_get_mac_addr(struct nfp_net *nn)
{
	u8 mac_addr[ETH_ALEN];

	put_unaligned_be32(nn_readl(nn, NFP_NET_CFG_MACADDR + 0), &mac_addr[0]);
	put_unaligned_be16(nn_readw(nn, NFP_NET_CFG_MACADDR + 6), &mac_addr[4]);

	if (!is_valid_ether_addr(mac_addr)) {
		eth_hw_addr_random(nn->dp.netdev);
		return;
	}

	ether_addr_copy(nn->dp.netdev->dev_addr, mac_addr);
	ether_addr_copy(nn->dp.netdev->perm_addr, mac_addr);
}