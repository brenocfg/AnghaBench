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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (void*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_free_frag (void*) ; 

__attribute__((used)) static void mvpp2_frag_free(const struct mvpp2_bm_pool *pool, void *data)
{
	if (likely(pool->frag_size <= PAGE_SIZE))
		skb_free_frag(data);
	else
		kfree(data);
}