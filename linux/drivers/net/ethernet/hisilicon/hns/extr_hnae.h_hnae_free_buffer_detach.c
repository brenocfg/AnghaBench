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
struct hnae_ring {struct hnae_desc_cb* desc_cb; TYPE_2__* q; } ;
struct hnae_desc_cb {int /*<<< orphan*/  dma; } ;
struct hnae_buf_ops {int /*<<< orphan*/  (* free_buffer ) (struct hnae_ring*,struct hnae_desc_cb*) ;} ;
struct TYPE_4__ {TYPE_1__* handle; } ;
struct TYPE_3__ {struct hnae_buf_ops* bops; } ;

/* Variables and functions */
 int /*<<< orphan*/  hnae_buffer_detach (struct hnae_ring*,int) ; 
 int /*<<< orphan*/  stub1 (struct hnae_ring*,struct hnae_desc_cb*) ; 

__attribute__((used)) static inline void hnae_free_buffer_detach(struct hnae_ring *ring, int i)
{
	struct hnae_buf_ops *bops = ring->q->handle->bops;
	struct hnae_desc_cb *cb = &ring->desc_cb[i];

	if (!ring->desc_cb[i].dma)
		return;

	hnae_buffer_detach(ring, i);
	bops->free_buffer(ring, cb);
}