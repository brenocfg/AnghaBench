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
 int EDMR_SRST_GETHER ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int sh_eth_read (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_eth_check_soft_reset(struct net_device *ndev)
{
	int cnt;

	for (cnt = 100; cnt > 0; cnt--) {
		if (!(sh_eth_read(ndev, EDMR) & EDMR_SRST_GETHER))
			return 0;
		mdelay(1);
	}

	netdev_err(ndev, "Device reset failed\n");
	return -ETIMEDOUT;
}