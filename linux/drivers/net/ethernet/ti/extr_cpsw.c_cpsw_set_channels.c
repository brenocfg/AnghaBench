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
struct ethtool_channels {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpsw_rx_handler ; 
 int cpsw_set_channels_common (struct net_device*,struct ethtool_channels*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpsw_set_channels(struct net_device *ndev,
			     struct ethtool_channels *chs)
{
	return cpsw_set_channels_common(ndev, chs, cpsw_rx_handler);
}