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
typedef  size_t u32 ;
struct vmci_handle_arr {size_t size; size_t capacity; size_t max_capacity; struct vmci_handle* entries; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int VMCI_ERROR_NO_MEM ; 
 int VMCI_SUCCESS ; 
 size_t handle_arr_calc_size (size_t) ; 
 struct vmci_handle_arr* krealloc (struct vmci_handle_arr*,size_t,int /*<<< orphan*/ ) ; 
 size_t min (size_t,size_t) ; 
 scalar_t__ unlikely (int) ; 

int vmci_handle_arr_append_entry(struct vmci_handle_arr **array_ptr,
				 struct vmci_handle handle)
{
	struct vmci_handle_arr *array = *array_ptr;

	if (unlikely(array->size >= array->capacity)) {
		/* reallocate. */
		struct vmci_handle_arr *new_array;
		u32 capacity_bump = min(array->max_capacity - array->capacity,
					array->capacity);
		size_t new_size = handle_arr_calc_size(array->capacity +
						       capacity_bump);

		if (array->size >= array->max_capacity)
			return VMCI_ERROR_NO_MEM;

		new_array = krealloc(array, new_size, GFP_ATOMIC);
		if (!new_array)
			return VMCI_ERROR_NO_MEM;

		new_array->capacity += capacity_bump;
		*array_ptr = array = new_array;
	}

	array->entries[array->size] = handle;
	array->size++;

	return VMCI_SUCCESS;
}