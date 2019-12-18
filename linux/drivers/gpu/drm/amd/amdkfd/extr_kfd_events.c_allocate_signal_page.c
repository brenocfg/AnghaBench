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
typedef  int /*<<< orphan*/  uint8_t ;
struct kfd_signal_page {int need_to_free_pages; void* kernel_address; } ;
struct kfd_process {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KFD_SIGNAL_EVENT_LIMIT ; 
 scalar_t__ UNSIGNALED_EVENT_SLOT ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  kfree (struct kfd_signal_page*) ; 
 struct kfd_signal_page* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct kfd_signal_page*,struct kfd_process*) ; 

__attribute__((used)) static struct kfd_signal_page *allocate_signal_page(struct kfd_process *p)
{
	void *backing_store;
	struct kfd_signal_page *page;

	page = kzalloc(sizeof(*page), GFP_KERNEL);
	if (!page)
		return NULL;

	backing_store = (void *) __get_free_pages(GFP_KERNEL,
					get_order(KFD_SIGNAL_EVENT_LIMIT * 8));
	if (!backing_store)
		goto fail_alloc_signal_store;

	/* Initialize all events to unsignaled */
	memset(backing_store, (uint8_t) UNSIGNALED_EVENT_SLOT,
	       KFD_SIGNAL_EVENT_LIMIT * 8);

	page->kernel_address = backing_store;
	page->need_to_free_pages = true;
	pr_debug("Allocated new event signal page at %p, for process %p\n",
			page, p);

	return page;

fail_alloc_signal_store:
	kfree(page);
	return NULL;
}