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
struct intel_vgpu_oos_page {int id; int /*<<< orphan*/  list; int /*<<< orphan*/  vm_list; void* mem; } ;
struct intel_gvt_gtt {int /*<<< orphan*/  oos_page_free_list_head; int /*<<< orphan*/  oos_page_use_list_head; } ;
struct intel_gvt {struct intel_gvt_gtt gtt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_spt_oos (struct intel_gvt*) ; 
 int /*<<< orphan*/  gvt_dbg_mm (char*,int) ; 
 int /*<<< orphan*/  kfree (struct intel_vgpu_oos_page*) ; 
 struct intel_vgpu_oos_page* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int preallocated_oos_pages ; 

__attribute__((used)) static int setup_spt_oos(struct intel_gvt *gvt)
{
	struct intel_gvt_gtt *gtt = &gvt->gtt;
	struct intel_vgpu_oos_page *oos_page;
	int i;
	int ret;

	INIT_LIST_HEAD(&gtt->oos_page_free_list_head);
	INIT_LIST_HEAD(&gtt->oos_page_use_list_head);

	for (i = 0; i < preallocated_oos_pages; i++) {
		oos_page = kzalloc(sizeof(*oos_page), GFP_KERNEL);
		if (!oos_page) {
			ret = -ENOMEM;
			goto fail;
		}
		oos_page->mem = (void *)__get_free_pages(GFP_KERNEL, 0);
		if (!oos_page->mem) {
			ret = -ENOMEM;
			kfree(oos_page);
			goto fail;
		}

		INIT_LIST_HEAD(&oos_page->list);
		INIT_LIST_HEAD(&oos_page->vm_list);
		oos_page->id = i;
		list_add_tail(&oos_page->list, &gtt->oos_page_free_list_head);
	}

	gvt_dbg_mm("%d oos pages preallocated\n", i);

	return 0;
fail:
	clean_spt_oos(gvt);
	return ret;
}