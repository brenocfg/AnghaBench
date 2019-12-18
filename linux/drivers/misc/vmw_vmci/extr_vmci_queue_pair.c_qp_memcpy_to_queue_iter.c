#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u64 ;
struct TYPE_5__ {int /*<<< orphan*/ * page; } ;
struct TYPE_4__ {void** vas; } ;
struct TYPE_6__ {TYPE_2__ h; TYPE_1__ g; } ;
struct vmci_queue_kern_if {TYPE_3__ u; scalar_t__ host; } ;
struct vmci_queue {struct vmci_queue_kern_if* kernel_if; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  copy_from_iter_full (int /*<<< orphan*/ *,size_t,struct iov_iter*) ; 
 void* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qp_memcpy_to_queue_iter(struct vmci_queue *queue,
				  u64 queue_offset,
				  struct iov_iter *from,
				  size_t size)
{
	struct vmci_queue_kern_if *kernel_if = queue->kernel_if;
	size_t bytes_copied = 0;

	while (bytes_copied < size) {
		const u64 page_index =
			(queue_offset + bytes_copied) / PAGE_SIZE;
		const size_t page_offset =
		    (queue_offset + bytes_copied) & (PAGE_SIZE - 1);
		void *va;
		size_t to_copy;

		if (kernel_if->host)
			va = kmap(kernel_if->u.h.page[page_index]);
		else
			va = kernel_if->u.g.vas[page_index + 1];
			/* Skip header. */

		if (size - bytes_copied > PAGE_SIZE - page_offset)
			/* Enough payload to fill up from this page. */
			to_copy = PAGE_SIZE - page_offset;
		else
			to_copy = size - bytes_copied;

		if (!copy_from_iter_full((u8 *)va + page_offset, to_copy,
					 from)) {
			if (kernel_if->host)
				kunmap(kernel_if->u.h.page[page_index]);
			return VMCI_ERROR_INVALID_ARGS;
		}
		bytes_copied += to_copy;
		if (kernel_if->host)
			kunmap(kernel_if->u.h.page[page_index]);
	}

	return VMCI_SUCCESS;
}