#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bits; } ;
struct dma_device {TYPE_1__ cap_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  bits; } ;
typedef  TYPE_2__ dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TX_TYPE_END ; 
 int /*<<< orphan*/  bitmap_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bitmap_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__dma_device_satisfies_mask(struct dma_device *device,
			    const dma_cap_mask_t *want)
{
	dma_cap_mask_t has;

	bitmap_and(has.bits, want->bits, device->cap_mask.bits,
		DMA_TX_TYPE_END);
	return bitmap_equal(want->bits, has.bits, DMA_TX_TYPE_END);
}