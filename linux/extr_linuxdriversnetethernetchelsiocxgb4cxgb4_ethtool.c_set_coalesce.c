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
struct ethtool_coalesce {int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  use_adaptive_rx_coalesce; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_adaptive_rx_setting (struct net_device*,int /*<<< orphan*/ ) ; 
 int set_rx_intr_params (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_coalesce(struct net_device *dev, struct ethtool_coalesce *c)
{
	set_adaptive_rx_setting(dev, c->use_adaptive_rx_coalesce);
	return set_rx_intr_params(dev, c->rx_coalesce_usecs,
				  c->rx_max_coalesced_frames);
}