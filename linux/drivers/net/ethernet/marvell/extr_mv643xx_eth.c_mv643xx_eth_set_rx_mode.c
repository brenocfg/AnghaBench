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
 int /*<<< orphan*/  mv643xx_eth_program_multicast_filter (struct net_device*) ; 
 int /*<<< orphan*/  mv643xx_eth_program_unicast_filter (struct net_device*) ; 

__attribute__((used)) static void mv643xx_eth_set_rx_mode(struct net_device *dev)
{
	mv643xx_eth_program_unicast_filter(dev);
	mv643xx_eth_program_multicast_filter(dev);
}