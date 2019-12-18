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
struct rtl8139_private {int regs_len; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct rtl8139_private* netdev_priv (struct net_device*) ; 
 scalar_t__ use_io ; 

__attribute__((used)) static int rtl8139_get_regs_len(struct net_device *dev)
{
	struct rtl8139_private *tp;
	/* TODO: we are too slack to do reg dumping for pio, for now */
	if (use_io)
		return 0;
	tp = netdev_priv(dev);
	return tp->regs_len;
}