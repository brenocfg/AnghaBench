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
struct ei_device {int /*<<< orphan*/  msg_enable; } ;

/* Variables and functions */
 struct ei_device* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ax_set_msglevel(struct net_device *dev, u32 v)
{
	struct ei_device *ei_local = netdev_priv(dev);

	ei_local->msg_enable = v;
}