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
struct fwnet_device {int peer_count; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_carrier_state(struct fwnet_device *dev)
{
	if (dev->peer_count > 1)
		netif_carrier_on(dev->netdev);
	else
		netif_carrier_off(dev->netdev);
}