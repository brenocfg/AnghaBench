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
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcs7830_data_set_multicast (struct net_device*) ; 
 int /*<<< orphan*/  mcs7830_hif_update_config (struct usbnet*) ; 
 int /*<<< orphan*/  mcs7830_hif_update_multicast_hash (struct usbnet*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mcs7830_set_multicast(struct net_device *net)
{
	struct usbnet *dev = netdev_priv(net);

	mcs7830_data_set_multicast(net);

	mcs7830_hif_update_multicast_hash(dev);
	mcs7830_hif_update_config(dev);
}