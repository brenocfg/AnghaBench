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
struct lance_private {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ HPLANCE_STATUS ; 
 int /*<<< orphan*/  lance_close (struct net_device*) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  out_8 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hplance_close(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);

	out_8(lp->base + HPLANCE_STATUS, 0);	/* disable interrupts at boardlevel */
	lance_close(dev);
	return 0;
}