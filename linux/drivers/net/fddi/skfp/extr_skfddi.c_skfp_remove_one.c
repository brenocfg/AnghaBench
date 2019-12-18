#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  iop; } ;
struct TYPE_3__ {int /*<<< orphan*/ * LocalRxBuffer; int /*<<< orphan*/  LocalRxBufferDMA; int /*<<< orphan*/ * SharedMemAddr; int /*<<< orphan*/  SharedMemDMA; int /*<<< orphan*/  SharedMemSize; } ;
struct s_smc {TYPE_2__ hw; TYPE_1__ os; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ioport_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct s_smc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void skfp_remove_one(struct pci_dev *pdev)
{
	struct net_device *p = pci_get_drvdata(pdev);
	struct s_smc *lp = netdev_priv(p);

	unregister_netdev(p);

	if (lp->os.SharedMemAddr) {
		dma_free_coherent(&pdev->dev,
				  lp->os.SharedMemSize,
				  lp->os.SharedMemAddr,
				  lp->os.SharedMemDMA);
		lp->os.SharedMemAddr = NULL;
	}
	if (lp->os.LocalRxBuffer) {
		dma_free_coherent(&pdev->dev,
				  MAX_FRAME_SIZE,
				  lp->os.LocalRxBuffer,
				  lp->os.LocalRxBufferDMA);
		lp->os.LocalRxBuffer = NULL;
	}
#ifdef MEM_MAPPED_IO
	iounmap(lp->hw.iop);
#else
	ioport_unmap(lp->hw.iop);
#endif
	pci_release_regions(pdev);
	free_netdev(p);

	pci_disable_device(pdev);
}