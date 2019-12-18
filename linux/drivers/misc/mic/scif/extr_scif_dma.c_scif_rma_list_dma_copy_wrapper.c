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
struct scif_dma_comp_cb {int is_cache; int dst_offset; int header_padding; struct scif_dma_comp_cb* temp_buf_to_free; int /*<<< orphan*/  sdev; int /*<<< orphan*/  temp_phys; struct scif_dma_comp_cb* temp_buf; int /*<<< orphan*/  len; int /*<<< orphan*/  dst_window; int /*<<< orphan*/ * dma_completion_func; struct scif_dma_comp_cb* cb_cookie; } ;
typedef  struct scif_dma_comp_cb u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct scif_endpt {int dummy; } ;
struct scif_copy_work {int src_offset; int dst_offset; int /*<<< orphan*/  fence_type; int /*<<< orphan*/  remote_dev; int /*<<< orphan*/  len; int /*<<< orphan*/  dst_window; TYPE_1__* src_window; struct scif_dma_comp_cb* comp_cb; scalar_t__ loopback; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int L1_CACHE_BYTES ; 
 struct scif_dma_comp_cb* PTR_ALIGN (struct scif_dma_comp_cb*,int) ; 
 int /*<<< orphan*/  SCIF_DMA_INTR ; 
 scalar_t__ SCIF_KMEM_UNALIGNED_BUF_SIZE ; 
 scalar_t__ SCIF_WINDOW_SELF ; 
 int _scif_rma_list_dma_copy_aligned (struct scif_copy_work*,struct dma_chan*) ; 
 scalar_t__ is_dma_copy_aligned (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  kfree (struct scif_dma_comp_cb*) ; 
 struct scif_dma_comp_cb* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scif_dma_comp_cb* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct scif_dma_comp_cb*) ; 
 struct scif_dma_comp_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int scif_map_single (int /*<<< orphan*/ *,struct scif_dma_comp_cb*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scif_rma_completion_cb ; 
 int scif_rma_list_cpu_copy (struct scif_copy_work*) ; 
 int scif_rma_list_dma_copy_aligned (struct scif_copy_work*,struct dma_chan*) ; 
 scalar_t__ scif_rma_list_dma_copy_unaligned (struct scif_copy_work*,struct scif_dma_comp_cb*,struct dma_chan*,int) ; 
 int /*<<< orphan*/  scif_rma_local_cpu_copy (int,TYPE_1__*,struct scif_dma_comp_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unaligned_cache ; 

__attribute__((used)) static int scif_rma_list_dma_copy_wrapper(struct scif_endpt *epd,
					  struct scif_copy_work *work,
					  struct dma_chan *chan, off_t loffset)
{
	int src_cache_off, dst_cache_off;
	s64 src_offset = work->src_offset, dst_offset = work->dst_offset;
	u8 *temp = NULL;
	bool src_local = true;
	struct scif_dma_comp_cb *comp_cb;
	int err;

	if (is_dma_copy_aligned(chan->device, 1, 1, 1))
		return _scif_rma_list_dma_copy_aligned(work, chan);

	src_cache_off = src_offset & (L1_CACHE_BYTES - 1);
	dst_cache_off = dst_offset & (L1_CACHE_BYTES - 1);

	if (dst_cache_off == src_cache_off)
		return scif_rma_list_dma_copy_aligned(work, chan);

	if (work->loopback)
		return scif_rma_list_cpu_copy(work);
	src_local = work->src_window->type == SCIF_WINDOW_SELF;

	/* Allocate dma_completion cb */
	comp_cb = kzalloc(sizeof(*comp_cb), GFP_KERNEL);
	if (!comp_cb)
		goto error;

	work->comp_cb = comp_cb;
	comp_cb->cb_cookie = comp_cb;
	comp_cb->dma_completion_func = &scif_rma_completion_cb;

	if (work->len + (L1_CACHE_BYTES << 1) < SCIF_KMEM_UNALIGNED_BUF_SIZE) {
		comp_cb->is_cache = false;
		/* Allocate padding bytes to align to a cache line */
		temp = kmalloc(work->len + (L1_CACHE_BYTES << 1),
			       GFP_KERNEL);
		if (!temp)
			goto free_comp_cb;
		comp_cb->temp_buf_to_free = temp;
		/* kmalloc(..) does not guarantee cache line alignment */
		if (!IS_ALIGNED((u64)temp, L1_CACHE_BYTES))
			temp = PTR_ALIGN(temp, L1_CACHE_BYTES);
	} else {
		comp_cb->is_cache = true;
		temp = kmem_cache_alloc(unaligned_cache, GFP_KERNEL);
		if (!temp)
			goto free_comp_cb;
		comp_cb->temp_buf_to_free = temp;
	}

	if (src_local) {
		temp += dst_cache_off;
		scif_rma_local_cpu_copy(work->src_offset, work->src_window,
					temp, work->len, true);
	} else {
		comp_cb->dst_window = work->dst_window;
		comp_cb->dst_offset = work->dst_offset;
		work->src_offset = work->src_offset - src_cache_off;
		comp_cb->len = work->len;
		work->len = ALIGN(work->len + src_cache_off, L1_CACHE_BYTES);
		comp_cb->header_padding = src_cache_off;
	}
	comp_cb->temp_buf = temp;

	err = scif_map_single(&comp_cb->temp_phys, temp,
			      work->remote_dev, SCIF_KMEM_UNALIGNED_BUF_SIZE);
	if (err)
		goto free_temp_buf;
	comp_cb->sdev = work->remote_dev;
	if (scif_rma_list_dma_copy_unaligned(work, temp, chan, src_local) < 0)
		goto free_temp_buf;
	if (!src_local)
		work->fence_type = SCIF_DMA_INTR;
	return 0;
free_temp_buf:
	if (comp_cb->is_cache)
		kmem_cache_free(unaligned_cache, comp_cb->temp_buf_to_free);
	else
		kfree(comp_cb->temp_buf_to_free);
free_comp_cb:
	kfree(comp_cb);
error:
	return -ENOMEM;
}