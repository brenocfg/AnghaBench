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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc52xx_fec_set_paddr (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc52xx_fec_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *sock = addr;

	memcpy(dev->dev_addr, sock->sa_data, dev->addr_len);

	mpc52xx_fec_set_paddr(dev, sock->sa_data);
	return 0;
}