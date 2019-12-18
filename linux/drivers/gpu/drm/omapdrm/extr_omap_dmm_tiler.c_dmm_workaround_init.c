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
typedef  int /*<<< orphan*/  u32 ;
struct dmm {int /*<<< orphan*/  wa_dma_handle; int /*<<< orphan*/  wa_dma_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  wa_dma_chan; int /*<<< orphan*/  wa_lock; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmm_workaround_init(struct dmm *dmm)
{
	dma_cap_mask_t mask;

	spin_lock_init(&dmm->wa_lock);

	dmm->wa_dma_data = dma_alloc_coherent(dmm->dev,  sizeof(u32),
					      &dmm->wa_dma_handle, GFP_KERNEL);
	if (!dmm->wa_dma_data)
		return -ENOMEM;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	dmm->wa_dma_chan = dma_request_channel(mask, NULL, NULL);
	if (!dmm->wa_dma_chan) {
		dma_free_coherent(dmm->dev, 4, dmm->wa_dma_data, dmm->wa_dma_handle);
		return -ENODEV;
	}

	return 0;
}