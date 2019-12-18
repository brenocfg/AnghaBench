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
typedef  int u16 ;
struct b43legacy_wldev {int /*<<< orphan*/ * dma_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_DMAIRQ_RX_DONE ; 
 int B43legacy_PIO_RXCTL ; 
 int B43legacy_PIO_RXCTL_DATAAVAILABLE ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 

__attribute__((used)) static void pio_irq_workaround(struct b43legacy_wldev *dev,
			       u16 base, int queueidx)
{
	u16 rxctl;

	rxctl = b43legacy_read16(dev, base + B43legacy_PIO_RXCTL);
	if (rxctl & B43legacy_PIO_RXCTL_DATAAVAILABLE)
		dev->dma_reason[queueidx] |= B43legacy_DMAIRQ_RX_DONE;
	else
		dev->dma_reason[queueidx] &= ~B43legacy_DMAIRQ_RX_DONE;
}