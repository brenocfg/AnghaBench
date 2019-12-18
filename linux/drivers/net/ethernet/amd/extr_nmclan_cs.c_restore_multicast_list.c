#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {unsigned int base_addr; int flags; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  multicast_num_addrs; } ;
typedef  TYPE_1__ mace_private ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MACE_MACCC ; 
 int MACE_MACCC_ENRCV ; 
 int MACE_MACCC_ENXMT ; 
 int MACE_MACCC_PROM ; 
 int /*<<< orphan*/  MACE_UTR ; 
 int MACE_UTR_LOOP_EXTERNAL ; 
 int /*<<< orphan*/  mace_write (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void restore_multicast_list(struct net_device *dev)
{
  unsigned int ioaddr = dev->base_addr;
  mace_private *lp = netdev_priv(dev);

  pr_debug("%s: restoring Rx mode to %d addresses.\n", dev->name,
	lp->multicast_num_addrs);

  if (dev->flags & IFF_PROMISC) {
    /* Promiscuous mode: receive all packets */
    mace_write(lp,ioaddr, MACE_UTR, MACE_UTR_LOOP_EXTERNAL);
    mace_write(lp, ioaddr, MACE_MACCC,
      MACE_MACCC_PROM | MACE_MACCC_ENXMT | MACE_MACCC_ENRCV
    );
  } else {
    /* Normal mode */
    mace_write(lp, ioaddr, MACE_UTR, MACE_UTR_LOOP_EXTERNAL);
    mace_write(lp, ioaddr, MACE_MACCC, MACE_MACCC_ENXMT | MACE_MACCC_ENRCV);
  }
}