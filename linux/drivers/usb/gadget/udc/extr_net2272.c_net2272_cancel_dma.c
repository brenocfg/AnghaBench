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
struct TYPE_2__ {scalar_t__ plx9054_base_addr; } ;
struct net2272 {int dev_id; scalar_t__ dma_busy; TYPE_1__ rdk1; } ;

/* Variables and functions */
 int CHANNEL_ABORT ; 
 int CHANNEL_CLEAR_INTERRUPT ; 
 int CHANNEL_DONE ; 
 scalar_t__ DMACSR0 ; 
#define  PCI_DEVICE_ID_RDK1 128 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void net2272_cancel_dma(struct net2272 *dev)
{
#ifdef CONFIG_USB_PCI
	switch (dev->dev_id) {
	case PCI_DEVICE_ID_RDK1:
		writeb(0, dev->rdk1.plx9054_base_addr + DMACSR0);
		writeb(1 << CHANNEL_ABORT, dev->rdk1.plx9054_base_addr + DMACSR0);
		while (!(readb(dev->rdk1.plx9054_base_addr + DMACSR0) &
		         (1 << CHANNEL_DONE)))
			continue;	/* wait for dma to stabalize */

		/* dma abort generates an interrupt */
		writeb(1 << CHANNEL_CLEAR_INTERRUPT,
			dev->rdk1.plx9054_base_addr + DMACSR0);
		break;
	}
#endif

	dev->dma_busy = 0;
}