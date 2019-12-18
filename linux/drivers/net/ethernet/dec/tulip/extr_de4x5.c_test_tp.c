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
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {int timeout; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DE4X5_SISR ; 
 int SISR_LKF ; 
 int SISR_NCR ; 
 int TIMER_CB ; 
 int inl (int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
test_tp(struct net_device *dev, s32 msec)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int sisr;

    if (lp->timeout < 0) {
	lp->timeout = msec/100;
    }

    sisr = (inl(DE4X5_SISR) & ~TIMER_CB) & (SISR_LKF | SISR_NCR);

    if (sisr && --lp->timeout) {
	sisr = 100 | TIMER_CB;
    } else {
	lp->timeout = -1;
    }

    return sisr;
}