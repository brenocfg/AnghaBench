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
union ib_gid {scalar_t__ raw; } ;
struct rxe_dev {int /*<<< orphan*/  ndev; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int dev_mc_add (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  ipv6_eth_mc_map (struct in6_addr*,unsigned char*) ; 

int rxe_mcast_add(struct rxe_dev *rxe, union ib_gid *mgid)
{
	int err;
	unsigned char ll_addr[ETH_ALEN];

	ipv6_eth_mc_map((struct in6_addr *)mgid->raw, ll_addr);
	err = dev_mc_add(rxe->ndev, ll_addr);

	return err;
}