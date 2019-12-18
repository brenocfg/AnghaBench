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
struct net_device_context {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  l4_hash; } ;
struct net_device {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  HV_DEFAULT_L4HASH ; 
 int /*<<< orphan*/  NETIF_F_LRO ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void netvsc_init_settings(struct net_device *dev)
{
	struct net_device_context *ndc = netdev_priv(dev);

	ndc->l4_hash = HV_DEFAULT_L4HASH;

	ndc->speed = SPEED_UNKNOWN;
	ndc->duplex = DUPLEX_FULL;

	dev->features = NETIF_F_LRO;
}