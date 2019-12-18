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
 int ANS_NWOK ; 
 int /*<<< orphan*/  DE4X5_IMR ; 
 int /*<<< orphan*/  DE4X5_SISR ; 
 int /*<<< orphan*/  DE4X5_STS ; 
 int SISR_ANS ; 
 int TIMER_CB ; 
 int inl (int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
test_ans(struct net_device *dev, s32 irqs, s32 irq_mask, s32 msec)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    s32 sts, ans;

    if (lp->timeout < 0) {
	lp->timeout = msec/100;
	outl(irq_mask, DE4X5_IMR);

	/* clear all pending interrupts */
	sts = inl(DE4X5_STS);
	outl(sts, DE4X5_STS);
    }

    ans = inl(DE4X5_SISR) & SISR_ANS;
    sts = inl(DE4X5_STS) & ~TIMER_CB;

    if (!(sts & irqs) && (ans ^ ANS_NWOK) && --lp->timeout) {
	sts = 100 | TIMER_CB;
    } else {
	lp->timeout = -1;
    }

    return sts;
}