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
typedef  scalar_t__ u16 ;
struct usbnet {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct cdc_mbim_state {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_IPS0_VLAN ; 
 scalar_t__ MBIM_IPS0_VID ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cdc_mbim_rx_kill_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
	struct usbnet *dev = netdev_priv(netdev);
	struct cdc_mbim_state *info = (void *)&dev->data;

	/* this is a request for an untagged IP session 0 */
	if (vid == MBIM_IPS0_VID)
		info->flags &= ~FLAG_IPS0_VLAN;
	return 0;
}