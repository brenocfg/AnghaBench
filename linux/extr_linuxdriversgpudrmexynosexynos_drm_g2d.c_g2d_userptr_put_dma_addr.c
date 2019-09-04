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
struct page {int dummy; } ;
struct g2d_data {int /*<<< orphan*/  drm_dev; } ;
struct g2d_cmdlist_userptr {struct g2d_cmdlist_userptr* sgt; int /*<<< orphan*/  list; int /*<<< orphan*/  out_of_list; int /*<<< orphan*/  vec; int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; scalar_t__ in_pool; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  IS_ERR (struct page**) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int frame_vector_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_vector_destroy (int /*<<< orphan*/ ) ; 
 struct page** frame_vector_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct g2d_cmdlist_userptr*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_vaddr_frames (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 
 int /*<<< orphan*/  sg_free_table (struct g2d_cmdlist_userptr*) ; 
 int /*<<< orphan*/  to_dma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void g2d_userptr_put_dma_addr(struct g2d_data *g2d,
					void *obj,
					bool force)
{
	struct g2d_cmdlist_userptr *g2d_userptr = obj;
	struct page **pages;

	if (!obj)
		return;

	if (force)
		goto out;

	atomic_dec(&g2d_userptr->refcount);

	if (atomic_read(&g2d_userptr->refcount) > 0)
		return;

	if (g2d_userptr->in_pool)
		return;

out:
	dma_unmap_sg(to_dma_dev(g2d->drm_dev), g2d_userptr->sgt->sgl,
			g2d_userptr->sgt->nents, DMA_BIDIRECTIONAL);

	pages = frame_vector_pages(g2d_userptr->vec);
	if (!IS_ERR(pages)) {
		int i;

		for (i = 0; i < frame_vector_count(g2d_userptr->vec); i++)
			set_page_dirty_lock(pages[i]);
	}
	put_vaddr_frames(g2d_userptr->vec);
	frame_vector_destroy(g2d_userptr->vec);

	if (!g2d_userptr->out_of_list)
		list_del_init(&g2d_userptr->list);

	sg_free_table(g2d_userptr->sgt);
	kfree(g2d_userptr->sgt);
	kfree(g2d_userptr);
}