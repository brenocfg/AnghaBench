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
typedef  int /*<<< orphan*/  u8 ;
struct binder_buffer {scalar_t__ data; int /*<<< orphan*/  entry; } ;
struct binder_alloc {int buffer_size; scalar_t__ buffer; int /*<<< orphan*/  buffers; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 TYPE_1__* binder_buffer_next (struct binder_buffer*) ; 
 scalar_t__ list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t binder_alloc_buffer_size(struct binder_alloc *alloc,
				       struct binder_buffer *buffer)
{
	if (list_is_last(&buffer->entry, &alloc->buffers))
		return (u8 *)alloc->buffer +
			alloc->buffer_size - (u8 *)buffer->data;
	return (u8 *)binder_buffer_next(buffer)->data - (u8 *)buffer->data;
}