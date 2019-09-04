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

/* Variables and functions */
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int PCI_DMA_BIDIRECTIONAL ; 
 int PCI_DMA_FROMDEVICE ; 
 int PCI_DMA_TODEVICE ; 

__attribute__((used)) static int xilly_pci_direction(int direction)
{
	switch (direction) {
	case DMA_TO_DEVICE:
		return PCI_DMA_TODEVICE;
	case DMA_FROM_DEVICE:
		return PCI_DMA_FROMDEVICE;
	default:
		return PCI_DMA_BIDIRECTIONAL;
	}
}