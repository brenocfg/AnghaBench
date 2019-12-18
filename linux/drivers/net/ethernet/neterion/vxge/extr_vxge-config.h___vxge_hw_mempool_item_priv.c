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
typedef  void u8 ;
typedef  size_t u32 ;
struct vxge_hw_mempool {size_t memblock_size; size_t item_size; size_t items_per_memblock; size_t items_priv_size; scalar_t__* memblocks_priv_arr; void** memblocks_arr; } ;
typedef  size_t ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  vxge_assert (int) ; 

__attribute__((used)) static inline void*
__vxge_hw_mempool_item_priv(
	struct vxge_hw_mempool *mempool,
	u32 memblock_idx,
	void *item,
	u32 *memblock_item_idx)
{
	ptrdiff_t offset;
	void *memblock = mempool->memblocks_arr[memblock_idx];


	offset = (u32)((u8 *)item - (u8 *)memblock);
	vxge_assert(offset >= 0 && (u32)offset < mempool->memblock_size);

	(*memblock_item_idx) = (u32) offset / mempool->item_size;
	vxge_assert((*memblock_item_idx) < mempool->items_per_memblock);

	return (u8 *)mempool->memblocks_priv_arr[memblock_idx] +
			    (*memblock_item_idx) * mempool->items_priv_size;
}