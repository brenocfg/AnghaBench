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
struct ethtool_wolinfo {scalar_t__ wolopts; scalar_t__ supported; } ;

/* Variables and functions */

__attribute__((used)) static void igbvf_get_wol(struct net_device *netdev,
			  struct ethtool_wolinfo *wol)
{
	wol->supported = 0;
	wol->wolopts = 0;
}