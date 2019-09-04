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
struct sonic_local {int /*<<< orphan*/  dma_bitmode; scalar_t__ rda_laddr; scalar_t__ rra_laddr; scalar_t__ tda_laddr; scalar_t__ cda_laddr; scalar_t__ descriptors_laddr; int /*<<< orphan*/ * rda; int /*<<< orphan*/ * rra; int /*<<< orphan*/ * tda; int /*<<< orphan*/ * cda; int /*<<< orphan*/ * descriptors; int /*<<< orphan*/  device; } ;
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SIZEOF_SONIC_CDA ; 
 int SIZEOF_SONIC_DESC ; 
 int SIZEOF_SONIC_RD ; 
 int SIZEOF_SONIC_TD ; 
 int SONIC_BUS_SCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SONIC_CRCT ; 
 int /*<<< orphan*/  SONIC_FAET ; 
 int /*<<< orphan*/  SONIC_MPT ; 
 int SONIC_NUM_RDS ; 
 int SONIC_NUM_TDS ; 
 int /*<<< orphan*/  SONIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macsonic_netdev_ops ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macsonic_init(struct net_device *dev)
{
	struct sonic_local* lp = netdev_priv(dev);

	/* Allocate the entire chunk of memory for the descriptors.
           Note that this cannot cross a 64K boundary. */
	lp->descriptors = dma_alloc_coherent(lp->device,
					     SIZEOF_SONIC_DESC *
					     SONIC_BUS_SCALE(lp->dma_bitmode),
					     &lp->descriptors_laddr,
					     GFP_KERNEL);
	if (lp->descriptors == NULL)
		return -ENOMEM;

	/* Now set up the pointers to point to the appropriate places */
	lp->cda = lp->descriptors;
	lp->tda = lp->cda + (SIZEOF_SONIC_CDA
	                     * SONIC_BUS_SCALE(lp->dma_bitmode));
	lp->rda = lp->tda + (SIZEOF_SONIC_TD * SONIC_NUM_TDS
	                     * SONIC_BUS_SCALE(lp->dma_bitmode));
	lp->rra = lp->rda + (SIZEOF_SONIC_RD * SONIC_NUM_RDS
	                     * SONIC_BUS_SCALE(lp->dma_bitmode));

	lp->cda_laddr = lp->descriptors_laddr;
	lp->tda_laddr = lp->cda_laddr + (SIZEOF_SONIC_CDA
	                     * SONIC_BUS_SCALE(lp->dma_bitmode));
	lp->rda_laddr = lp->tda_laddr + (SIZEOF_SONIC_TD * SONIC_NUM_TDS
	                     * SONIC_BUS_SCALE(lp->dma_bitmode));
	lp->rra_laddr = lp->rda_laddr + (SIZEOF_SONIC_RD * SONIC_NUM_RDS
	                     * SONIC_BUS_SCALE(lp->dma_bitmode));

	dev->netdev_ops = &macsonic_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	/*
	 * clear tally counter
	 */
	SONIC_WRITE(SONIC_CRCT, 0xffff);
	SONIC_WRITE(SONIC_FAET, 0xffff);
	SONIC_WRITE(SONIC_MPT, 0xffff);

	return 0;
}