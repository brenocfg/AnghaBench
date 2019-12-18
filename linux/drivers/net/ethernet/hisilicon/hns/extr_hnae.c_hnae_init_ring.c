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
struct hnae_ring {scalar_t__ desc_num; scalar_t__ buf_size; int flags; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/ * desc_cb; int /*<<< orphan*/  desc_dma_addr; int /*<<< orphan*/  desc; int /*<<< orphan*/  coal_param; struct hnae_queue* q; } ;
struct hnae_queue {TYPE_1__* handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  coal_param; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int hnae_alloc_buffers (struct hnae_ring*) ; 
 int hnae_alloc_desc (struct hnae_ring*) ; 
 int /*<<< orphan*/  hnae_free_desc (struct hnae_ring*) ; 
 scalar_t__ is_rx_ring (struct hnae_ring*) ; 
 int /*<<< orphan*/ * kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hnae_init_ring(struct hnae_queue *q, struct hnae_ring *ring, int flags)
{
	int ret;

	if (ring->desc_num <= 0 || ring->buf_size <= 0)
		return -EINVAL;

	ring->q = q;
	ring->flags = flags;
	ring->coal_param = q->handle->coal_param;
	assert(!ring->desc && !ring->desc_cb && !ring->desc_dma_addr);

	/* not matter for tx or rx ring, the ntc and ntc start from 0 */
	assert(ring->next_to_use == 0);
	assert(ring->next_to_clean == 0);

	ring->desc_cb = kcalloc(ring->desc_num, sizeof(ring->desc_cb[0]),
			GFP_KERNEL);
	if (!ring->desc_cb) {
		ret = -ENOMEM;
		goto out;
	}

	ret = hnae_alloc_desc(ring);
	if (ret)
		goto out_with_desc_cb;

	if (is_rx_ring(ring)) {
		ret = hnae_alloc_buffers(ring);
		if (ret)
			goto out_with_desc;
	}

	return 0;

out_with_desc:
	hnae_free_desc(ring);
out_with_desc_cb:
	kfree(ring->desc_cb);
	ring->desc_cb = NULL;
out:
	return ret;
}