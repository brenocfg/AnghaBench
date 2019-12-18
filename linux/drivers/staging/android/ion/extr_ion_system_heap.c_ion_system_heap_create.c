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
struct ion_heap {char* name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ion_heap*) ; 
 int PTR_ERR (struct ion_heap*) ; 
 struct ion_heap* __ion_system_heap_create () ; 
 int /*<<< orphan*/  ion_device_add_heap (struct ion_heap*) ; 

__attribute__((used)) static int ion_system_heap_create(void)
{
	struct ion_heap *heap;

	heap = __ion_system_heap_create();
	if (IS_ERR(heap))
		return PTR_ERR(heap);
	heap->name = "ion_system_heap";

	ion_device_add_heap(heap);

	return 0;
}