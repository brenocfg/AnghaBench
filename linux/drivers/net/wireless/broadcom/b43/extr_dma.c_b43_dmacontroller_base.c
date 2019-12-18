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
typedef  int /*<<< orphan*/  const u16 ;
typedef  enum b43_dmatype { ____Placeholder_b43_dmatype } b43_dmatype ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int B43_DMA_64BIT ; 
#define  B43_MMIO_DMA32_BASE0 139 
#define  B43_MMIO_DMA32_BASE1 138 
#define  B43_MMIO_DMA32_BASE2 137 
#define  B43_MMIO_DMA32_BASE3 136 
#define  B43_MMIO_DMA32_BASE4 135 
#define  B43_MMIO_DMA32_BASE5 134 
#define  B43_MMIO_DMA64_BASE0 133 
#define  B43_MMIO_DMA64_BASE1 132 
#define  B43_MMIO_DMA64_BASE2 131 
#define  B43_MMIO_DMA64_BASE3 130 
#define  B43_MMIO_DMA64_BASE4 129 
#define  B43_MMIO_DMA64_BASE5 128 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 

__attribute__((used)) static u16 b43_dmacontroller_base(enum b43_dmatype type, int controller_idx)
{
	static const u16 map64[] = {
		B43_MMIO_DMA64_BASE0,
		B43_MMIO_DMA64_BASE1,
		B43_MMIO_DMA64_BASE2,
		B43_MMIO_DMA64_BASE3,
		B43_MMIO_DMA64_BASE4,
		B43_MMIO_DMA64_BASE5,
	};
	static const u16 map32[] = {
		B43_MMIO_DMA32_BASE0,
		B43_MMIO_DMA32_BASE1,
		B43_MMIO_DMA32_BASE2,
		B43_MMIO_DMA32_BASE3,
		B43_MMIO_DMA32_BASE4,
		B43_MMIO_DMA32_BASE5,
	};

	if (type == B43_DMA_64BIT) {
		B43_WARN_ON(!(controller_idx >= 0 &&
			      controller_idx < ARRAY_SIZE(map64)));
		return map64[controller_idx];
	}
	B43_WARN_ON(!(controller_idx >= 0 &&
		      controller_idx < ARRAY_SIZE(map32)));
	return map32[controller_idx];
}