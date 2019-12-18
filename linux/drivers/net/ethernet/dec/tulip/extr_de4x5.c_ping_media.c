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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {int timeout; size_t tmp; size_t tx_new; int txRingSize; TYPE_1__* tx_ring; int /*<<< orphan*/  frame; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE4X5_SISR ; 
 int /*<<< orphan*/  DE4X5_TPD ; 
 int /*<<< orphan*/  POLL_DEMAND ; 
 int SISR_NCR ; 
 int TD_ES ; 
 int TD_FS ; 
 int TD_LS ; 
 int TIMER_CB ; 
 int T_OWN ; 
 int inl (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_packet (struct net_device*,int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ping_media(struct net_device *dev, int msec)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int sisr;

    if (lp->timeout < 0) {
	lp->timeout = msec/100;

	lp->tmp = lp->tx_new;                /* Remember the ring position */
	load_packet(dev, lp->frame, TD_LS | TD_FS | sizeof(lp->frame), (struct sk_buff *)1);
	lp->tx_new = (lp->tx_new + 1) % lp->txRingSize;
	outl(POLL_DEMAND, DE4X5_TPD);
    }

    sisr = inl(DE4X5_SISR);

    if ((!(sisr & SISR_NCR)) &&
	((s32)le32_to_cpu(lp->tx_ring[lp->tmp].status) < 0) &&
	 (--lp->timeout)) {
	sisr = 100 | TIMER_CB;
    } else {
	if ((!(sisr & SISR_NCR)) &&
	    !(le32_to_cpu(lp->tx_ring[lp->tmp].status) & (T_OWN | TD_ES)) &&
	    lp->timeout) {
	    sisr = 0;
	} else {
	    sisr = 1;
	}
	lp->timeout = -1;
    }

    return sisr;
}