#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hnae_ring {TYPE_4__* desc; int /*<<< orphan*/ * desc_cb; TYPE_3__* q; } ;
struct TYPE_8__ {scalar_t__ addr; } ;
struct TYPE_7__ {TYPE_2__* handle; } ;
struct TYPE_6__ {TYPE_1__* bops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* unmap_buffer ) (struct hnae_ring*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hnae_ring*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hnae_buffer_detach(struct hnae_ring *ring, int i)
{
	ring->q->handle->bops->unmap_buffer(ring, &ring->desc_cb[i]);
	ring->desc[i].addr = 0;
}