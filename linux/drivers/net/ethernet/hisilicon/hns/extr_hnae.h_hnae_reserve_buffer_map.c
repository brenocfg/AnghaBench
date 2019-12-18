#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hnae_ring {TYPE_2__* q; } ;
struct hnae_desc_cb {int dummy; } ;
struct hnae_buf_ops {int (* alloc_buffer ) (struct hnae_ring*,struct hnae_desc_cb*) ;int (* map_buffer ) (struct hnae_ring*,struct hnae_desc_cb*) ;int /*<<< orphan*/  (* free_buffer ) (struct hnae_ring*,struct hnae_desc_cb*) ;} ;
struct TYPE_4__ {TYPE_1__* handle; } ;
struct TYPE_3__ {struct hnae_buf_ops* bops; } ;

/* Variables and functions */
 int stub1 (struct hnae_ring*,struct hnae_desc_cb*) ; 
 int stub2 (struct hnae_ring*,struct hnae_desc_cb*) ; 
 int /*<<< orphan*/  stub3 (struct hnae_ring*,struct hnae_desc_cb*) ; 

__attribute__((used)) static inline int hnae_reserve_buffer_map(struct hnae_ring *ring,
					  struct hnae_desc_cb *cb)
{
	struct hnae_buf_ops *bops = ring->q->handle->bops;
	int ret;

	ret = bops->alloc_buffer(ring, cb);
	if (ret)
		goto out;

	ret = bops->map_buffer(ring, cb);
	if (ret)
		goto out_with_buf;

	return 0;

out_with_buf:
	bops->free_buffer(ring, cb);
out:
	return ret;
}