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
 int /*<<< orphan*/  igbvf_set_multi (struct net_device*) ; 
 int /*<<< orphan*/  igbvf_set_uni (struct net_device*) ; 

__attribute__((used)) static void igbvf_set_rx_mode(struct net_device *netdev)
{
	igbvf_set_multi(netdev);
	igbvf_set_uni(netdev);
}