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
typedef  scalar_t__ u32 ;
struct vmci_handle_arr {scalar_t__ size; scalar_t__ max_capacity; scalar_t__ capacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ VMCI_HANDLE_ARRAY_DEFAULT_CAPACITY ; 
 int /*<<< orphan*/  handle_arr_calc_size (scalar_t__) ; 
 struct vmci_handle_arr* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

struct vmci_handle_arr *vmci_handle_arr_create(u32 capacity, u32 max_capacity)
{
	struct vmci_handle_arr *array;

	if (max_capacity == 0 || capacity > max_capacity)
		return NULL;

	if (capacity == 0)
		capacity = min((u32)VMCI_HANDLE_ARRAY_DEFAULT_CAPACITY,
			       max_capacity);

	array = kmalloc(handle_arr_calc_size(capacity), GFP_ATOMIC);
	if (!array)
		return NULL;

	array->capacity = capacity;
	array->max_capacity = max_capacity;
	array->size = 0;

	return array;
}