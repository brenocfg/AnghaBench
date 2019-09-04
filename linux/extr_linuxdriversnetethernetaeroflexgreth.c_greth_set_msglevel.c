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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct greth_private {int /*<<< orphan*/  msg_enable; } ;

/* Variables and functions */
 struct greth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void greth_set_msglevel(struct net_device *dev, u32 value)
{
	struct greth_private *greth = netdev_priv(dev);
	greth->msg_enable = value;
}