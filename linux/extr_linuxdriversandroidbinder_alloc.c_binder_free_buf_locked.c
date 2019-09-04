#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct binder_buffer {int free; scalar_t__ data; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  entry; scalar_t__ async_transaction; int /*<<< orphan*/ * transaction; int /*<<< orphan*/  extra_buffers_size; int /*<<< orphan*/  offsets_size; int /*<<< orphan*/  data_size; } ;
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
struct binder_alloc {scalar_t__ buffer; size_t free_async_space; int /*<<< orphan*/  free_buffers; TYPE_1__ buffers; int /*<<< orphan*/  allocated_buffers; int /*<<< orphan*/  pid; int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */
 size_t ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BINDER_DEBUG_BUFFER_ALLOC ; 
 int /*<<< orphan*/  BINDER_DEBUG_BUFFER_ALLOC_ASYNC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PAGE_ALIGN (uintptr_t) ; 
 uintptr_t PAGE_MASK ; 
 size_t binder_alloc_buffer_size (struct binder_alloc*,struct binder_buffer*) ; 
 int /*<<< orphan*/  binder_alloc_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct binder_buffer* binder_buffer_next (struct binder_buffer*) ; 
 struct binder_buffer* binder_buffer_prev (struct binder_buffer*) ; 
 int /*<<< orphan*/  binder_delete_free_buffer (struct binder_alloc*,struct binder_buffer*) ; 
 int /*<<< orphan*/  binder_insert_free_buffer (struct binder_alloc*,struct binder_buffer*) ; 
 int /*<<< orphan*/  binder_update_page_range (struct binder_alloc*,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  list_is_last (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void binder_free_buf_locked(struct binder_alloc *alloc,
				   struct binder_buffer *buffer)
{
	size_t size, buffer_size;

	buffer_size = binder_alloc_buffer_size(alloc, buffer);

	size = ALIGN(buffer->data_size, sizeof(void *)) +
		ALIGN(buffer->offsets_size, sizeof(void *)) +
		ALIGN(buffer->extra_buffers_size, sizeof(void *));

	binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
		     "%d: binder_free_buf %pK size %zd buffer_size %zd\n",
		      alloc->pid, buffer, size, buffer_size);

	BUG_ON(buffer->free);
	BUG_ON(size > buffer_size);
	BUG_ON(buffer->transaction != NULL);
	BUG_ON(buffer->data < alloc->buffer);
	BUG_ON(buffer->data > alloc->buffer + alloc->buffer_size);

	if (buffer->async_transaction) {
		alloc->free_async_space += size + sizeof(struct binder_buffer);

		binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC_ASYNC,
			     "%d: binder_free_buf size %zd async free %zd\n",
			      alloc->pid, size, alloc->free_async_space);
	}

	binder_update_page_range(alloc, 0,
		(void *)PAGE_ALIGN((uintptr_t)buffer->data),
		(void *)(((uintptr_t)buffer->data + buffer_size) & PAGE_MASK));

	rb_erase(&buffer->rb_node, &alloc->allocated_buffers);
	buffer->free = 1;
	if (!list_is_last(&buffer->entry, &alloc->buffers)) {
		struct binder_buffer *next = binder_buffer_next(buffer);

		if (next->free) {
			rb_erase(&next->rb_node, &alloc->free_buffers);
			binder_delete_free_buffer(alloc, next);
		}
	}
	if (alloc->buffers.next != &buffer->entry) {
		struct binder_buffer *prev = binder_buffer_prev(buffer);

		if (prev->free) {
			binder_delete_free_buffer(alloc, buffer);
			rb_erase(&prev->rb_node, &alloc->free_buffers);
			buffer = prev;
		}
	}
	binder_insert_free_buffer(alloc, buffer);
}