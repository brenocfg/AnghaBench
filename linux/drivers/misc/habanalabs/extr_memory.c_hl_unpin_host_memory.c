#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct hl_userptr {TYPE_2__* sgt; int /*<<< orphan*/  job_node; int /*<<< orphan*/  vec; int /*<<< orphan*/  dir; scalar_t__ dma_mapped; } ;
struct hl_device {TYPE_1__* asic_funcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hl_dma_unmap_sg ) (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page**) ; 
 int frame_vector_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_vector_destroy (int /*<<< orphan*/ ) ; 
 struct page** frame_vector_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_debugfs_remove_userptr (struct hl_device*,struct hl_userptr*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_vaddr_frames (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hl_unpin_host_memory(struct hl_device *hdev, struct hl_userptr *userptr)
{
	struct page **pages;

	hl_debugfs_remove_userptr(hdev, userptr);

	if (userptr->dma_mapped)
		hdev->asic_funcs->hl_dma_unmap_sg(hdev,
				userptr->sgt->sgl,
				userptr->sgt->nents,
				userptr->dir);

	pages = frame_vector_pages(userptr->vec);
	if (!IS_ERR(pages)) {
		int i;

		for (i = 0; i < frame_vector_count(userptr->vec); i++)
			set_page_dirty_lock(pages[i]);
	}
	put_vaddr_frames(userptr->vec);
	frame_vector_destroy(userptr->vec);

	list_del(&userptr->job_node);

	sg_free_table(userptr->sgt);
	kfree(userptr->sgt);

	return 0;
}