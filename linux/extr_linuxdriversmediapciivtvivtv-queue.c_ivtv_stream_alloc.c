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
struct ivtv_stream {int buffers; scalar_t__ dma; int buf_size; int /*<<< orphan*/  name; int /*<<< orphan*/  q_free; struct ivtv* itv; int /*<<< orphan*/ * sg_dma; void* sg_handle; struct ivtv_buffer* sg_processing; struct ivtv_buffer* sg_pending; scalar_t__ sg_processing_size; scalar_t__ sg_pending_size; } ;
struct ivtv_sg_host_element {int dummy; } ;
struct ivtv_sg_element {int dummy; } ;
struct ivtv_buffer {int /*<<< orphan*/ * buf; void* dma_handle; int /*<<< orphan*/  list; } ;
struct ivtv {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  IVTV_ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_DMA_NONE ; 
 scalar_t__ PCI_DMA_TODEVICE ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  ivtv_buf_sync_for_cpu (struct ivtv_stream*,struct ivtv_buffer*) ; 
 int /*<<< orphan*/  ivtv_enqueue (struct ivtv_stream*,struct ivtv_buffer*,int /*<<< orphan*/ *) ; 
 scalar_t__ ivtv_might_use_dma (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_stream_free (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_stream_sync_for_cpu (struct ivtv_stream*) ; 
 int /*<<< orphan*/  kfree (struct ivtv_buffer*) ; 
 int /*<<< orphan*/ * kmalloc (int,int) ; 
 void* kzalloc (int,int) ; 
 void* pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__) ; 

int ivtv_stream_alloc(struct ivtv_stream *s)
{
	struct ivtv *itv = s->itv;
	int SGsize = sizeof(struct ivtv_sg_host_element) * s->buffers;
	int i;

	if (s->buffers == 0)
		return 0;

	IVTV_DEBUG_INFO("Allocate %s%s stream: %d x %d buffers (%dkB total)\n",
		s->dma != PCI_DMA_NONE ? "DMA " : "",
		s->name, s->buffers, s->buf_size, s->buffers * s->buf_size / 1024);

	s->sg_pending = kzalloc(SGsize, GFP_KERNEL|__GFP_NOWARN);
	if (s->sg_pending == NULL) {
		IVTV_ERR("Could not allocate sg_pending for %s stream\n", s->name);
		return -ENOMEM;
	}
	s->sg_pending_size = 0;

	s->sg_processing = kzalloc(SGsize, GFP_KERNEL|__GFP_NOWARN);
	if (s->sg_processing == NULL) {
		IVTV_ERR("Could not allocate sg_processing for %s stream\n", s->name);
		kfree(s->sg_pending);
		s->sg_pending = NULL;
		return -ENOMEM;
	}
	s->sg_processing_size = 0;

	s->sg_dma = kzalloc(sizeof(struct ivtv_sg_element),
					GFP_KERNEL|__GFP_NOWARN);
	if (s->sg_dma == NULL) {
		IVTV_ERR("Could not allocate sg_dma for %s stream\n", s->name);
		kfree(s->sg_pending);
		s->sg_pending = NULL;
		kfree(s->sg_processing);
		s->sg_processing = NULL;
		return -ENOMEM;
	}
	if (ivtv_might_use_dma(s)) {
		s->sg_handle = pci_map_single(itv->pdev, s->sg_dma,
				sizeof(struct ivtv_sg_element), PCI_DMA_TODEVICE);
		ivtv_stream_sync_for_cpu(s);
	}

	/* allocate stream buffers. Initially all buffers are in q_free. */
	for (i = 0; i < s->buffers; i++) {
		struct ivtv_buffer *buf = kzalloc(sizeof(struct ivtv_buffer),
						GFP_KERNEL|__GFP_NOWARN);

		if (buf == NULL)
			break;
		buf->buf = kmalloc(s->buf_size + 256, GFP_KERNEL|__GFP_NOWARN);
		if (buf->buf == NULL) {
			kfree(buf);
			break;
		}
		INIT_LIST_HEAD(&buf->list);
		if (ivtv_might_use_dma(s)) {
			buf->dma_handle = pci_map_single(s->itv->pdev,
				buf->buf, s->buf_size + 256, s->dma);
			ivtv_buf_sync_for_cpu(s, buf);
		}
		ivtv_enqueue(s, buf, &s->q_free);
	}
	if (i == s->buffers)
		return 0;
	IVTV_ERR("Couldn't allocate buffers for %s stream\n", s->name);
	ivtv_stream_free(s);
	return -ENOMEM;
}