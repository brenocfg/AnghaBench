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
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_g_rq_cache ; 
 int /*<<< orphan*/  pblk_rec_cache ; 
 int /*<<< orphan*/  pblk_w_rq_cache ; 
 int /*<<< orphan*/  pblk_ws_cache ; 

__attribute__((used)) static void pblk_free_global_caches(struct pblk *pblk)
{
	kmem_cache_destroy(pblk_ws_cache);
	kmem_cache_destroy(pblk_rec_cache);
	kmem_cache_destroy(pblk_g_rq_cache);
	kmem_cache_destroy(pblk_w_rq_cache);
}