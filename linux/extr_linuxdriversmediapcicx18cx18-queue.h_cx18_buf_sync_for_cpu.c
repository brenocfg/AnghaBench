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
struct cx18_stream {int /*<<< orphan*/  dma; int /*<<< orphan*/  buf_size; TYPE_1__* cx; } ;
struct cx18_buffer {int /*<<< orphan*/  dma_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cx18_buf_sync_for_cpu(struct cx18_stream *s,
	struct cx18_buffer *buf)
{
	pci_dma_sync_single_for_cpu(s->cx->pci_dev, buf->dma_handle,
				s->buf_size, s->dma);
}