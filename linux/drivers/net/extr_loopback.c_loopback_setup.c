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
 int /*<<< orphan*/  eth_header_ops ; 
 int /*<<< orphan*/  gen_lo_setup (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loopback_dev_free ; 
 int /*<<< orphan*/  loopback_ethtool_ops ; 
 int /*<<< orphan*/  loopback_ops ; 

__attribute__((used)) static void loopback_setup(struct net_device *dev)
{
	gen_lo_setup(dev, (64 * 1024), &loopback_ethtool_ops, &eth_header_ops,
		     &loopback_ops, loopback_dev_free);
}