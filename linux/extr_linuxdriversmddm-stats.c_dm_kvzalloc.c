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

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_NOMEMALLOC ; 
 int /*<<< orphan*/  claim_shared_memory (size_t) ; 
 int /*<<< orphan*/  free_shared_memory (size_t) ; 
 void* kvzalloc_node (size_t,int,int) ; 

__attribute__((used)) static void *dm_kvzalloc(size_t alloc_size, int node)
{
	void *p;

	if (!claim_shared_memory(alloc_size))
		return NULL;

	p = kvzalloc_node(alloc_size, GFP_KERNEL | __GFP_NOMEMALLOC, node);
	if (p)
		return p;

	free_shared_memory(alloc_size);

	return NULL;
}