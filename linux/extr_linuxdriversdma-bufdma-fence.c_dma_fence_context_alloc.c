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
typedef  unsigned int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int atomic64_add_return (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_context_counter ; 

u64 dma_fence_context_alloc(unsigned num)
{
	WARN_ON(!num);
	return atomic64_add_return(num, &dma_fence_context_counter) - num;
}