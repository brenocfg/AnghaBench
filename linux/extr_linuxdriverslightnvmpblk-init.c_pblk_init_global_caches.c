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
struct pblk_rec_ctx {int dummy; } ;
struct pblk_line_ws {int dummy; } ;
struct pblk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (void*) ; 
 void* pblk_g_rq_cache ; 
 int pblk_g_rq_size ; 
 int /*<<< orphan*/  pblk_lock ; 
 void* pblk_rec_cache ; 
 void* pblk_w_rq_cache ; 
 int pblk_w_rq_size ; 
 void* pblk_ws_cache ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pblk_init_global_caches(struct pblk *pblk)
{
	down_write(&pblk_lock);
	pblk_ws_cache = kmem_cache_create("pblk_blk_ws",
				sizeof(struct pblk_line_ws), 0, 0, NULL);
	if (!pblk_ws_cache) {
		up_write(&pblk_lock);
		return -ENOMEM;
	}

	pblk_rec_cache = kmem_cache_create("pblk_rec",
				sizeof(struct pblk_rec_ctx), 0, 0, NULL);
	if (!pblk_rec_cache) {
		kmem_cache_destroy(pblk_ws_cache);
		up_write(&pblk_lock);
		return -ENOMEM;
	}

	pblk_g_rq_cache = kmem_cache_create("pblk_g_rq", pblk_g_rq_size,
				0, 0, NULL);
	if (!pblk_g_rq_cache) {
		kmem_cache_destroy(pblk_ws_cache);
		kmem_cache_destroy(pblk_rec_cache);
		up_write(&pblk_lock);
		return -ENOMEM;
	}

	pblk_w_rq_cache = kmem_cache_create("pblk_w_rq", pblk_w_rq_size,
				0, 0, NULL);
	if (!pblk_w_rq_cache) {
		kmem_cache_destroy(pblk_ws_cache);
		kmem_cache_destroy(pblk_rec_cache);
		kmem_cache_destroy(pblk_g_rq_cache);
		up_write(&pblk_lock);
		return -ENOMEM;
	}
	up_write(&pblk_lock);

	return 0;
}