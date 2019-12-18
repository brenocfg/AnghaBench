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
struct ion_heap {int flags; } ;
struct ion_buffer {struct ion_heap* heap; } ;

/* Variables and functions */
 int ION_HEAP_FLAG_DEFER_FREE ; 
 int /*<<< orphan*/  ion_buffer_destroy (struct ion_buffer*) ; 
 int /*<<< orphan*/  ion_heap_freelist_add (struct ion_heap*,struct ion_buffer*) ; 

__attribute__((used)) static void _ion_buffer_destroy(struct ion_buffer *buffer)
{
	struct ion_heap *heap = buffer->heap;

	if (heap->flags & ION_HEAP_FLAG_DEFER_FREE)
		ion_heap_freelist_add(heap, buffer);
	else
		ion_buffer_destroy(buffer);
}