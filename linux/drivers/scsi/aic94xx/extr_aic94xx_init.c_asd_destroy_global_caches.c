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
 int /*<<< orphan*/ * asd_ascb_cache ; 
 int /*<<< orphan*/ * asd_dma_token_cache ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asd_destroy_global_caches(void)
{
	kmem_cache_destroy(asd_dma_token_cache);
	asd_dma_token_cache = NULL;

	kmem_cache_destroy(asd_ascb_cache);
	asd_ascb_cache = NULL;
}