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
struct mthca_icm_iter {size_t page_idx; TYPE_1__* chunk; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mem; } ;

/* Variables and functions */
 unsigned long sg_dma_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned long mthca_icm_size(struct mthca_icm_iter *iter)
{
	return sg_dma_len(&iter->chunk->mem[iter->page_idx]);
}