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
typedef  int /*<<< orphan*/  uint64_t ;
struct kfd_signal_page {void* kernel_address; } ;
struct kfd_process {int /*<<< orphan*/  signal_mapped_size; struct kfd_signal_page* signal_page; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KFD_SIGNAL_EVENT_LIMIT ; 
 scalar_t__ UNSIGNALED_EVENT_SLOT ; 
 struct kfd_signal_page* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

int kfd_event_page_set(struct kfd_process *p, void *kernel_address,
		       uint64_t size)
{
	struct kfd_signal_page *page;

	if (p->signal_page)
		return -EBUSY;

	page = kzalloc(sizeof(*page), GFP_KERNEL);
	if (!page)
		return -ENOMEM;

	/* Initialize all events to unsignaled */
	memset(kernel_address, (uint8_t) UNSIGNALED_EVENT_SLOT,
	       KFD_SIGNAL_EVENT_LIMIT * 8);

	page->kernel_address = kernel_address;

	p->signal_page = page;
	p->signal_mapped_size = size;

	return 0;
}