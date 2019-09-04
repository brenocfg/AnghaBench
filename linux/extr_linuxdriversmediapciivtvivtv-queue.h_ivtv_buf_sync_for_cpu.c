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
struct ivtv_stream {int /*<<< orphan*/  dma; scalar_t__ buf_size; TYPE_1__* itv; } ;
struct ivtv_buffer {int /*<<< orphan*/  dma_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ ivtv_use_dma (struct ivtv_stream*) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ivtv_buf_sync_for_cpu(struct ivtv_stream *s, struct ivtv_buffer *buf)
{
	if (ivtv_use_dma(s))
		pci_dma_sync_single_for_cpu(s->itv->pdev, buf->dma_handle,
				s->buf_size + 256, s->dma);
}