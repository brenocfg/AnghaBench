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
struct ivtv_stream {int /*<<< orphan*/  sg_handle; TYPE_1__* itv; } ;
struct ivtv_sg_element {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ ivtv_use_dma (struct ivtv_stream*) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ivtv_stream_sync_for_device(struct ivtv_stream *s)
{
	if (ivtv_use_dma(s))
		pci_dma_sync_single_for_device(s->itv->pdev, s->sg_handle,
			sizeof(struct ivtv_sg_element), PCI_DMA_TODEVICE);
}