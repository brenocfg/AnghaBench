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
struct net2272 {int dev_id; TYPE_1__ rdk1; } ;

/* Variables and functions */
 int CHANNEL_ENABLE ; 
 int CHANNEL_START ; 
 scalar_t__ DMACSR0 ; 
#define  PCI_DEVICE_ID_RDK1 128 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void
net2272_start_dma(struct net2272 *dev)
{
	/* start platform's dma controller */
#ifdef CONFIG_USB_PCI
	switch (dev->dev_id) {
	case PCI_DEVICE_ID_RDK1:
		writeb((1 << CHANNEL_ENABLE) | (1 << CHANNEL_START),
			dev->rdk1.plx9054_base_addr + DMACSR0);
		break;
	}
#endif
}