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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ L1_CACHE_ALIGN (scalar_t__) ; 
 size_t L1_CACHE_BYTES ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 

void *
xpc_kmalloc_cacheline_aligned(size_t size, gfp_t flags, void **base)
{
	/* see if kmalloc will give us cachline aligned memory by default */
	*base = kmalloc(size, flags);
	if (*base == NULL)
		return NULL;

	if ((u64)*base == L1_CACHE_ALIGN((u64)*base))
		return *base;

	kfree(*base);

	/* nope, we'll have to do it ourselves */
	*base = kmalloc(size + L1_CACHE_BYTES, flags);
	if (*base == NULL)
		return NULL;

	return (void *)L1_CACHE_ALIGN((u64)*base);
}