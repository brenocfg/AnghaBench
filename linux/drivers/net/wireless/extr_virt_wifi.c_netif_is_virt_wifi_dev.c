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
struct net_device {int /*<<< orphan*/  rx_handler; } ;

/* Variables and functions */
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 scalar_t__ virt_wifi_rx_handler ; 

__attribute__((used)) static bool netif_is_virt_wifi_dev(const struct net_device *dev)
{
	return rcu_access_pointer(dev->rx_handler) == virt_wifi_rx_handler;
}