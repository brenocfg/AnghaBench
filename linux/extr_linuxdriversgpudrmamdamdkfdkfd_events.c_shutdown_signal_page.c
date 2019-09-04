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
struct kfd_signal_page {scalar_t__ kernel_address; scalar_t__ need_to_free_pages; } ;
struct kfd_process {struct kfd_signal_page* signal_page; } ;

/* Variables and functions */
 int KFD_SIGNAL_EVENT_LIMIT ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  kfree (struct kfd_signal_page*) ; 

__attribute__((used)) static void shutdown_signal_page(struct kfd_process *p)
{
	struct kfd_signal_page *page = p->signal_page;

	if (page) {
		if (page->need_to_free_pages)
			free_pages((unsigned long)page->kernel_address,
				   get_order(KFD_SIGNAL_EVENT_LIMIT * 8));
		kfree(page);
	}
}