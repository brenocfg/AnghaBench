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
struct mvpp2_bm_pool {scalar_t__ frag_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PAGE_SIZE ; 
 void* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 void* netdev_alloc_frag (scalar_t__) ; 

__attribute__((used)) static void *mvpp2_frag_alloc(const struct mvpp2_bm_pool *pool)
{
	if (likely(pool->frag_size <= PAGE_SIZE))
		return netdev_alloc_frag(pool->frag_size);
	else
		return kmalloc(pool->frag_size, GFP_ATOMIC);
}