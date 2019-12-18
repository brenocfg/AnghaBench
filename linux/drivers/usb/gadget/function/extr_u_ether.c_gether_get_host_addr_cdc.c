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
struct eth_dev {int /*<<< orphan*/  host_mac; } ;

/* Variables and functions */
 int EINVAL ; 
 struct eth_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

int gether_get_host_addr_cdc(struct net_device *net, char *host_addr, int len)
{
	struct eth_dev *dev;

	if (len < 13)
		return -EINVAL;

	dev = netdev_priv(net);
	snprintf(host_addr, len, "%pm", dev->host_mac);

	return strlen(host_addr);
}