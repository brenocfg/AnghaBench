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
struct ethtool_wolinfo {int supported; scalar_t__ wolopts; } ;

/* Variables and functions */
 int WAKE_MAGIC ; 
 int WAKE_PHY ; 

__attribute__((used)) static void uli526x_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	wol->supported = WAKE_PHY | WAKE_MAGIC;
	wol->wolopts = 0;
}