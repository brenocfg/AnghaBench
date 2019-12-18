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
struct mlx4_icm_iter {size_t page_idx; TYPE_2__* chunk; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/ * sg; TYPE_1__* buf; scalar_t__ coherent; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline dma_addr_t mlx4_icm_addr(struct mlx4_icm_iter *iter)
{
	if (iter->chunk->coherent)
		return iter->chunk->buf[iter->page_idx].dma_addr;
	else
		return sg_dma_address(&iter->chunk->sg[iter->page_idx]);
}