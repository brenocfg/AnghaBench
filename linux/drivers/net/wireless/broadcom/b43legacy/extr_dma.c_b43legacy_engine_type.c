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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct b43legacy_wldev {int dummy; } ;
typedef  enum b43legacy_dmatype { ____Placeholder_b43legacy_dmatype } b43legacy_dmatype ;

/* Variables and functions */
 int B43legacy_DMA32_TXADDREXT_MASK ; 
 scalar_t__ B43legacy_DMA32_TXCTL ; 
 int B43legacy_DMA_30BIT ; 
 int B43legacy_DMA_32BIT ; 
 scalar_t__ b43legacy_dmacontroller_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,scalar_t__) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,scalar_t__,int) ; 

__attribute__((used)) static enum b43legacy_dmatype b43legacy_engine_type(struct b43legacy_wldev *dev)
{
	u32 tmp;
	u16 mmio_base;

	mmio_base = b43legacy_dmacontroller_base(0, 0);
	b43legacy_write32(dev,
			mmio_base + B43legacy_DMA32_TXCTL,
			B43legacy_DMA32_TXADDREXT_MASK);
	tmp = b43legacy_read32(dev, mmio_base +
			       B43legacy_DMA32_TXCTL);
	if (tmp & B43legacy_DMA32_TXADDREXT_MASK)
		return B43legacy_DMA_32BIT;
	return B43legacy_DMA_30BIT;
}