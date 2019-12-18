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
struct net_device {int base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** slcan_devs ; 

__attribute__((used)) static void slc_free_netdev(struct net_device *dev)
{
	int i = dev->base_addr;

	slcan_devs[i] = NULL;
}