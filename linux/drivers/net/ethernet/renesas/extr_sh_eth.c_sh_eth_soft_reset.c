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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDMR ; 
 int /*<<< orphan*/  EDMR_SRST_ETHER ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  sh_eth_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_eth_soft_reset(struct net_device *ndev)
{
	sh_eth_modify(ndev, EDMR, EDMR_SRST_ETHER, EDMR_SRST_ETHER);
	mdelay(3);
	sh_eth_modify(ndev, EDMR, EDMR_SRST_ETHER, 0);

	return 0;
}