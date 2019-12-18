#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ a; } ;
struct TYPE_6__ {TYPE_1__ fddi_canon_addr; int /*<<< orphan*/  irq; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {scalar_t__ SharedMemSize; int /*<<< orphan*/ * LocalRxBuffer; int /*<<< orphan*/  LocalRxBufferDMA; TYPE_3__ pdev; int /*<<< orphan*/ * SharedMemAddr; int /*<<< orphan*/  SharedMemDMA; scalar_t__ SharedMemHeap; int /*<<< orphan*/  DriverLock; int /*<<< orphan*/  base_addr; } ;
struct s_smc {TYPE_2__ hw; TYPE_4__ os; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;
typedef  TYPE_4__ skfddi_priv ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  card_stop (struct s_smc*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mac_drv_check_space () ; 
 scalar_t__ mac_drv_init (struct s_smc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct s_smc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  read_address (struct s_smc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smt_reset_defaults (struct s_smc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static  int skfp_driver_init(struct net_device *dev)
{
	struct s_smc *smc = netdev_priv(dev);
	skfddi_priv *bp = &smc->os;
	int err = -EIO;

	pr_debug("entering skfp_driver_init\n");

	// set the io address in private structures
	bp->base_addr = dev->base_addr;

	// Get the interrupt level from the PCI Configuration Table
	smc->hw.irq = dev->irq;

	spin_lock_init(&bp->DriverLock);
	
	// Allocate invalid frame
	bp->LocalRxBuffer = dma_alloc_coherent(&bp->pdev.dev, MAX_FRAME_SIZE,
					       &bp->LocalRxBufferDMA,
					       GFP_ATOMIC);
	if (!bp->LocalRxBuffer) {
		printk("could not allocate mem for ");
		printk("LocalRxBuffer: %d byte\n", MAX_FRAME_SIZE);
		goto fail;
	}

	// Determine the required size of the 'shared' memory area.
	bp->SharedMemSize = mac_drv_check_space();
	pr_debug("Memory for HWM: %ld\n", bp->SharedMemSize);
	if (bp->SharedMemSize > 0) {
		bp->SharedMemSize += 16;	// for descriptor alignment

		bp->SharedMemAddr = dma_alloc_coherent(&bp->pdev.dev,
						       bp->SharedMemSize,
						       &bp->SharedMemDMA,
						       GFP_ATOMIC);
		if (!bp->SharedMemAddr) {
			printk("could not allocate mem for ");
			printk("hardware module: %ld byte\n",
			       bp->SharedMemSize);
			goto fail;
		}

	} else {
		bp->SharedMemAddr = NULL;
	}

	bp->SharedMemHeap = 0;

	card_stop(smc);		// Reset adapter.

	pr_debug("mac_drv_init()..\n");
	if (mac_drv_init(smc) != 0) {
		pr_debug("mac_drv_init() failed\n");
		goto fail;
	}
	read_address(smc, NULL);
	pr_debug("HW-Addr: %pMF\n", smc->hw.fddi_canon_addr.a);
	memcpy(dev->dev_addr, smc->hw.fddi_canon_addr.a, ETH_ALEN);

	smt_reset_defaults(smc, 0);

	return 0;

fail:
	if (bp->SharedMemAddr) {
		dma_free_coherent(&bp->pdev.dev,
				  bp->SharedMemSize,
				  bp->SharedMemAddr,
				  bp->SharedMemDMA);
		bp->SharedMemAddr = NULL;
	}
	if (bp->LocalRxBuffer) {
		dma_free_coherent(&bp->pdev.dev, MAX_FRAME_SIZE,
				  bp->LocalRxBuffer, bp->LocalRxBufferDMA);
		bp->LocalRxBuffer = NULL;
	}
	return err;
}