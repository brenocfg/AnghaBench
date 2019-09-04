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
struct TYPE_5__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  copy_align; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_prep_dma_interrupt; int /*<<< orphan*/  device_prep_dma_imm_data; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  cap_mask; } ;
struct mic_dma_device {int start_ch; TYPE_2__ dma_dev; TYPE_1__* mic_ch; } ;
typedef  enum mic_dma_chan_owner { ____Placeholder_mic_dma_chan_owner } mic_dma_chan_owner ;
struct TYPE_6__ {int /*<<< orphan*/  device_node; TYPE_2__* device; } ;
struct TYPE_4__ {TYPE_3__ api_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIC_DMA_ALIGN_SHIFT ; 
 int MIC_DMA_CHAN_HOST ; 
 int MIC_DMA_NUM_CHAN ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_3__*) ; 
 int dmaenginem_async_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mic_dma_alloc_chan_resources ; 
 int /*<<< orphan*/  mic_dma_free_chan_resources ; 
 int /*<<< orphan*/  mic_dma_issue_pending ; 
 int /*<<< orphan*/  mic_dma_prep_interrupt_lock ; 
 int /*<<< orphan*/  mic_dma_prep_memcpy_lock ; 
 int /*<<< orphan*/  mic_dma_prep_status_lock ; 
 int /*<<< orphan*/  mic_dma_tx_status ; 

__attribute__((used)) static int mic_dma_register_dma_device(struct mic_dma_device *mic_dma_dev,
				       enum mic_dma_chan_owner owner)
{
	int i, first_chan = mic_dma_dev->start_ch;

	dma_cap_zero(mic_dma_dev->dma_dev.cap_mask);
	/*
	 * This dma engine is not capable of host memory to host memory
	 * transfers
	 */
	dma_cap_set(DMA_MEMCPY, mic_dma_dev->dma_dev.cap_mask);

	if (MIC_DMA_CHAN_HOST == owner)
		dma_cap_set(DMA_PRIVATE, mic_dma_dev->dma_dev.cap_mask);
	mic_dma_dev->dma_dev.device_alloc_chan_resources =
		mic_dma_alloc_chan_resources;
	mic_dma_dev->dma_dev.device_free_chan_resources =
		mic_dma_free_chan_resources;
	mic_dma_dev->dma_dev.device_tx_status = mic_dma_tx_status;
	mic_dma_dev->dma_dev.device_prep_dma_memcpy = mic_dma_prep_memcpy_lock;
	mic_dma_dev->dma_dev.device_prep_dma_imm_data =
		mic_dma_prep_status_lock;
	mic_dma_dev->dma_dev.device_prep_dma_interrupt =
		mic_dma_prep_interrupt_lock;
	mic_dma_dev->dma_dev.device_issue_pending = mic_dma_issue_pending;
	mic_dma_dev->dma_dev.copy_align = MIC_DMA_ALIGN_SHIFT;
	INIT_LIST_HEAD(&mic_dma_dev->dma_dev.channels);
	for (i = first_chan; i < first_chan + MIC_DMA_NUM_CHAN; i++) {
		mic_dma_dev->mic_ch[i].api_ch.device = &mic_dma_dev->dma_dev;
		dma_cookie_init(&mic_dma_dev->mic_ch[i].api_ch);
		list_add_tail(&mic_dma_dev->mic_ch[i].api_ch.device_node,
			      &mic_dma_dev->dma_dev.channels);
	}
	return dmaenginem_async_device_register(&mic_dma_dev->dma_dev);
}