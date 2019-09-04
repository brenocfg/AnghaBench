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
struct TYPE_2__ {int csr15; } ;
struct de4x5_private {int chipset; TYPE_1__ cache; } ;
typedef  int s32 ;

/* Variables and functions */
 int DC21140 ; 
 int DC2114x ; 
 int /*<<< orphan*/  DE4X5_GEP ; 
 int /*<<< orphan*/  DE4X5_SIGR ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gep_wr(s32 data, struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;

    if (lp->chipset == DC21140) {
	outl(data, DE4X5_GEP);
    } else if ((lp->chipset & ~0x00ff) == DC2114x) {
	outl((data<<16) | lp->cache.csr15, DE4X5_SIGR);
    }
}