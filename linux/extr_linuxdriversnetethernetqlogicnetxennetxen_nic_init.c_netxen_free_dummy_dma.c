#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; int /*<<< orphan*/  phys_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {TYPE_3__* pdev; TYPE_1__ dummy_dma; TYPE_2__ ahw; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETXEN_DMA_WATCHDOG_CTRL ; 
 int /*<<< orphan*/  NETXEN_HOST_DUMMY_DMA_SIZE ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_free_consistent (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void netxen_free_dummy_dma(struct netxen_adapter *adapter)
{
	int i = 100;
	u32 ctrl;

	if (!NX_IS_REVISION_P2(adapter->ahw.revision_id))
		return;

	if (!adapter->dummy_dma.addr)
		return;

	ctrl = NXRD32(adapter, NETXEN_DMA_WATCHDOG_CTRL);
	if ((ctrl & 0x1) != 0) {
		NXWR32(adapter, NETXEN_DMA_WATCHDOG_CTRL, (ctrl | 0x2));

		while ((ctrl & 0x1) != 0) {

			msleep(50);

			ctrl = NXRD32(adapter, NETXEN_DMA_WATCHDOG_CTRL);

			if (--i == 0)
				break;
		}
	}

	if (i) {
		pci_free_consistent(adapter->pdev,
			    NETXEN_HOST_DUMMY_DMA_SIZE,
			    adapter->dummy_dma.addr,
			    adapter->dummy_dma.phys_addr);
		adapter->dummy_dma.addr = NULL;
	} else
		dev_err(&adapter->pdev->dev, "dma_watchdog_shutdown failed\n");
}