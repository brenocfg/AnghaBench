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
struct can_bittiming_const {int dummy; } ;
struct can_bittiming {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 

__attribute__((used)) static int can_calc_bittiming(struct net_device *dev, struct can_bittiming *bt,
			      const struct can_bittiming_const *btc)
{
	netdev_err(dev, "bit-timing calculation not available\n");
	return -EINVAL;
}