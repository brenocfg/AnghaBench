#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {long timeout; size_t active; TYPE_1__* phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE4X5_MII ; 
 int TIMER_CB ; 
 int mii_rd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
test_mii_reg(struct net_device *dev, int reg, int mask, bool pol, long msec)
{
    struct de4x5_private *lp = netdev_priv(dev);
    int test;
    u_long iobase = dev->base_addr;

    if (lp->timeout < 0) {
	lp->timeout = msec/100;
    }

    reg = mii_rd((u_char)reg, lp->phy[lp->active].addr, DE4X5_MII) & mask;
    test = (reg ^ (pol ? ~0 : 0)) & mask;

    if (test && --lp->timeout) {
	reg = 100 | TIMER_CB;
    } else {
	lp->timeout = -1;
    }

    return reg;
}