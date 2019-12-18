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
struct srpt_send_ioctx {int dummy; } ;
struct srpt_recv_ioctx {int dummy; } ;
struct srpt_ioctx {int index; int offset; } ;
struct srpt_device {int dummy; } ;
struct kmem_cache {int dummy; } ;
typedef  int /*<<< orphan*/  ring ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kvfree (struct srpt_ioctx**) ; 
 struct srpt_ioctx** kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct srpt_ioctx* srpt_alloc_ioctx (struct srpt_device*,int,struct kmem_cache*,int) ; 
 int /*<<< orphan*/  srpt_free_ioctx (struct srpt_device*,struct srpt_ioctx*,struct kmem_cache*,int) ; 

__attribute__((used)) static struct srpt_ioctx **srpt_alloc_ioctx_ring(struct srpt_device *sdev,
				int ring_size, int ioctx_size,
				struct kmem_cache *buf_cache,
				int alignment_offset,
				enum dma_data_direction dir)
{
	struct srpt_ioctx **ring;
	int i;

	WARN_ON(ioctx_size != sizeof(struct srpt_recv_ioctx) &&
		ioctx_size != sizeof(struct srpt_send_ioctx));

	ring = kvmalloc_array(ring_size, sizeof(ring[0]), GFP_KERNEL);
	if (!ring)
		goto out;
	for (i = 0; i < ring_size; ++i) {
		ring[i] = srpt_alloc_ioctx(sdev, ioctx_size, buf_cache, dir);
		if (!ring[i])
			goto err;
		ring[i]->index = i;
		ring[i]->offset = alignment_offset;
	}
	goto out;

err:
	while (--i >= 0)
		srpt_free_ioctx(sdev, ring[i], buf_cache, dir);
	kvfree(ring);
	ring = NULL;
out:
	return ring;
}