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
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_PFNUM_UNICAST ; 
 int /*<<< orphan*/  AVE_RXMAC1R ; 
 int /*<<< orphan*/  AVE_RXMAC2R ; 
 int /*<<< orphan*/  ave_hw_write_macaddr (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ave_pfsel_set_macaddr (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ave_macaddr_init(struct net_device *ndev)
{
	ave_hw_write_macaddr(ndev, ndev->dev_addr, AVE_RXMAC1R, AVE_RXMAC2R);

	/* pfsel unicast entry */
	ave_pfsel_set_macaddr(ndev, AVE_PFNUM_UNICAST, ndev->dev_addr, 6);
}