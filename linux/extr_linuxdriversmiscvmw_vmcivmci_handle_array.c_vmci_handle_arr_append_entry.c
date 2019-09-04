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
struct vmci_handle_arr {size_t size; size_t capacity; struct vmci_handle* entries; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t VMCI_ARR_CAP_MULT ; 
 size_t handle_arr_calc_size (size_t) ; 
 struct vmci_handle_arr* krealloc (struct vmci_handle_arr*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void vmci_handle_arr_append_entry(struct vmci_handle_arr **array_ptr,
				  struct vmci_handle handle)
{
	struct vmci_handle_arr *array = *array_ptr;

	if (unlikely(array->size >= array->capacity)) {
		/* reallocate. */
		struct vmci_handle_arr *new_array;
		size_t new_capacity = array->capacity * VMCI_ARR_CAP_MULT;
		size_t new_size = handle_arr_calc_size(new_capacity);

		new_array = krealloc(array, new_size, GFP_ATOMIC);
		if (!new_array)
			return;

		new_array->capacity = new_capacity;
		*array_ptr = array = new_array;
	}

	array->entries[array->size] = handle;
	array->size++;
}