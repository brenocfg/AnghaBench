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
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {size_t rx_new; int rxRingSize; TYPE_1__* rx_ring; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE4X5_OMR ; 
 int /*<<< orphan*/  DE4X5_STS ; 
 int OMR_SR ; 
 int /*<<< orphan*/  R_OWN ; 
 int STS_RS ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int inl (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
de4x5_rx_ovfc(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int omr;

    omr = inl(DE4X5_OMR);
    outl(omr & ~OMR_SR, DE4X5_OMR);
    while (inl(DE4X5_STS) & STS_RS);

    for (; (s32)le32_to_cpu(lp->rx_ring[lp->rx_new].status)>=0;) {
	lp->rx_ring[lp->rx_new].status = cpu_to_le32(R_OWN);
	lp->rx_new = (lp->rx_new + 1) % lp->rxRingSize;
    }

    outl(omr, DE4X5_OMR);

    return 0;
}